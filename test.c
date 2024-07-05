#include <stdio.h>
#include "MESSAGES/channel_matrx.pb-c.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#define DO_PROTO

#ifdef DO_PROTO
  #define TRANSPORT_ADDR "127.0.0.1"
  #define TRANSPORT_PORT 7776
#endif


int main() {
    int32_t attach_UEs = 1;
    int32_t iteration = 0;
    int32_t interval = 40000;
    printf("========= Protest UEs test. =========\n");
    while (1 == 1){
        iteration = iteration % 120;
        usleep(interval);
        if (iteration % 12 == 0){
#ifdef DO_PROTO
            // [SRS MATRIX PROTO LOGIC START HERE]
            NRMatrix__UESRSPACK* multi_ues_pack;
            multi_ues_pack = malloc(sizeof(NRMatrix__UESRSPACK));
            nrmatrix__ue__srs__pack__init(multi_ues_pack);
            multi_ues_pack->n_ue_info = attach_UEs;

            NRMatrix__NRSRSPACK** ues_info;
            ues_info = malloc(sizeof(NRMatrix__NRSRSPACK) * attach_UEs);
#endif
            printf("In Iteration [%d] Attach UE nums : %d.\n", iteration, attach_UEs);
            for (int i = 0; i< attach_UEs; i ++){
#ifdef DO_PROTO
            // [SRS MATRIX PROTO LOGIC START HERE]
            NRMatrix__NRSRSPACK* channel_matrix_list;
            channel_matrix_list = malloc(sizeof(NRMatrix__NRSRSPACK));
            nrmatrix__nr__srs__pack__init(channel_matrix_list);
            channel_matrix_list->n_matrix = 2;
            NRMatrix__NRSRSINFO ** channel_data;
            channel_data = malloc(sizeof(NRMatrix__NRSRSINFO) 
                                  * 2
                                  * 104);
#endif
                for (int uI = 0; uI <1; uI ++){
                    for (int gI = 0; gI < 2; gI++){
#ifdef DO_PROTO
                        NRMatrix__NRSRSINFO * srs_channel_matrix;
                        srs_channel_matrix = malloc(sizeof(NRMatrix__NRSRSINFO));
                        nrmatrix__nr__srs__info__init(srs_channel_matrix);
                        srs_channel_matrix->n_prb_item = 104;
                        NRMatrix__RESULT ** matrix_elements;
                        matrix_elements = malloc(sizeof(matrix_elements) * 104);
#endif
                        for (int pI = 0; pI < 104; pI ++){

                            int csi_re = rand() % 100 + 1;
                            int csi_im = rand() % 100 + 1;
#ifdef DO_PROTO                  
                            NRMatrix__RESULT * matrix_element;
                            matrix_element =malloc(sizeof(NRMatrix__RESULT));
                            nrmatrix__result__init(matrix_element);
                            matrix_element->real = csi_re;
                            matrix_element->image = csi_im;
                            matrix_elements[pI] = matrix_element;
#endif
                        } // (int pI = 0; pI < 104; pI ++)
#ifdef DO_PROTO
                        srs_channel_matrix->prb_item = matrix_elements;
                        channel_data[uI * 2 + gI] = srs_channel_matrix;
#endif
                    } // for (int gI = 0; gI < 2; gI++)
                } // for (int uI = 0; uI <1; uI ++)
#ifdef DO_PROTO            
                channel_matrix_list->matrix = channel_data;
                channel_matrix_list->ue_id = i;
                ues_info[i] = channel_matrix_list;
                printf("    NR_SRS_PACK[%d] is packed. \n",i);
#endif
            } // for (int i = 0; i< attach_UEs; i ++)

              // TOTAL SEND
#ifdef DO_PROTO
            // Socket Send Protobuf
            multi_ues_pack->ue_info = ues_info;
            int length = nrmatrix__ue__srs__pack__get_packed_size(multi_ues_pack);
            void *buffer = malloc(sizeof(uint8_t) * length);
            nrmatrix__ue__srs__pack__pack(multi_ues_pack,buffer);
            int sockfd = socket(AF_INET,SOCK_DGRAM, 0);
            if(sockfd < 0){
                perror("sockfd");
                return -1;
            }
            struct sockaddr_in ser;
            ser.sin_family = AF_INET;
            ser.sin_port = htons(TRANSPORT_PORT);
            ser.sin_addr.s_addr = inet_addr(TRANSPORT_ADDR);
            sendto(sockfd, buffer, length, 0, (struct sockaddr *)&ser, sizeof(ser));
            close(sockfd);
            // free(multi_ues_pack);
            printf("Sucessfully send data.\n");
            printf("=========================================\n");
#endif
        } // iteration % 12 == 0

        iteration += 1;

        if (iteration / 12 > 3) {
            attach_UEs = 2;
        }
        else{
            attach_UEs = 1;
        }
    }
}