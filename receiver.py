from google.protobuf import json_format
import socket
from MESSAGES import channel_matrx_pb2
import json


if __name__ == "__main__":
    

    while True:
        LISTEN_FROM = "127.0.0.1"
        PORT = 7776

        server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
        address = (LISTEN_FROM, PORT)
        server_socket.bind(address)
        ddd = channel_matrx_pb2.UE_SRS_PACK()

        receive_data, _ = server_socket.recvfrom(65535)
        server_socket.close()
        ddd.ParseFromString(receive_data)
        jsonStringRequest=json.loads(json_format.MessageToJson(ddd))

        ueinfo = jsonStringRequest['ueInfo']
        print(f"Recevied UE info is {len(ueinfo)}")



    
