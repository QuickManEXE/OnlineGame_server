// �T�[�o�� WinSock2

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

int main() {

	// �|�[�g�ԍ�
	int port_number = 12345;

	// Windows Sockets�d�l�Ɋւ�������i�[����\����
	WSADATA wsa_data;

	// WinSock�̏���������(Version 2.0)
	if (WSAStartup(MAKEWORD(2, 0), &wsa_data) != 0) {
		std::cerr << "Winsock�̏��������s(WSAStartup)" << std::endl;
	}

	// �T�[�o���\�P�b�g�쐬
	int src_socket;

	// sockaddr_in�\���̂̍쐬�ƃ|�[�g�ԍ��AIP�^�C�v�̓���
	struct sockaddr_in src_addr;
	memset(&src_addr, 0, sizeof(src_addr));
	src_addr.sin_port = htons(port_number);
	src_addr.sin_family = AF_INET;
	src_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// AF_INET��ipv4��IP�v���g�R�� & SOCK_STREAM��TCP�v���g�R��
	src_socket = socket(AF_INET, SOCK_STREAM, 0);

	// �T�[�o���̃\�P�b�g������IP�A�h���X�ƃ|�[�g�ɕR�t����
	bind(src_socket, (struct sockaddr*)&src_addr, sizeof(src_addr));

	// �N���C�A���g���̃\�P�b�g�ݒ�1
	int dst_socket;
	struct sockaddr_in dst_addr;
	int dst_addr_size = sizeof(dst_addr);

	// �ڑ��̑Ҏ���J�n����
	listen(src_socket, 1);

	// ����M�Ɏg�p����o�b�t�@
	char recv_buf1[256], recv_buf2[256];
	char send_buf[256];

	struct CVector3D {
		float x;
		float y;
		float z;
		CVector3D() { x = 0; y = 0; z = 0; }
		CVector3D(float _x, float _y, float _z) {
			x = _x; y = _y; z = _z;
		}
	};

	CVector3D pos;

	std::cout << "��M��������1�� : " << pos.x << pos.y << pos.z << std::endl;

	CVector3D send_pos(100,200,300);

	// �N���C�A���g����̐ڑ��҂����[�v�֐�
	while (1) {

		std::cout << "�N���C�A���g����̐ڑ��҂�1" << std::endl;

		// �N���C�A���g����̐ڑ�����M����
		dst_socket = accept(src_socket, (struct sockaddr*)&dst_addr, &dst_addr_size);

		std::cout << "�N���C�A���g����̐ڑ��L��1" << std::endl;


		// �ڑ���̏���
		while (1) {

			int status;

			////�N���C�A���g�P����̎�M
			////�p�P�b�g�̎�M(recv�͐�������Ǝ�M�����f�[�^�̃o�C�g����ԋp�B�ؒf��0�A���s��-1���ԋp�����
			//int recv1_result = recv(dst_socket, recv_buf1, sizeof(char) * 256, 0);
			//if (recv1_result == 0 || recv1_result == -1) {
			//	status = closesocket(dst_socket); break;
			//}
			//std::cout << "��M��������1�� : " << recv_buf1 << std::endl;

			//�N���C�A���g�P����̎�M
			//�p�P�b�g�̎�M(recv�͐�������Ǝ�M�����f�[�^�̃o�C�g����ԋp�B�ؒf��0�A���s��-1���ԋp�����
			

			// ���ʂ��i�[�����p�P�b�g�̑��M
			send(dst_socket,  (char*)(&send_pos), sizeof(send_pos), 0);
			
			int recv1_result = recv(dst_socket, (char*)(&send_pos), sizeof(send_pos), 0);
			if (recv1_result == 0 || recv1_result == -1) {
				status = closesocket(dst_socket); break;
			}
			std::cout << "��M��������1�� : " << send_pos.x << send_pos.y << send_pos.z << std::endl;

			
		}
	}

	// WinSock�̏I������
	WSACleanup();

	return 0;
}