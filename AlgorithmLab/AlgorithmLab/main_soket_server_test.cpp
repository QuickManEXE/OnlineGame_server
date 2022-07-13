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


	// �N���C�A���g���̃\�P�b�g�ݒ�2
	int dst_socket2;
	struct sockaddr_in dst_addr2;
	int dst_addr_size2 = sizeof(dst_addr2);

	// �ڑ��̑Ҏ���J�n����
	//listen(src_socket, 1);

	// ����M�Ɏg�p����o�b�t�@
	char recv_buf1_2[256], recv_buf2_2[256];
	char send_buf2[256];

	// �N���C�A���g����̐ڑ��҂����[�v�֐�
	while (1) {

		std::cout << "�N���C�A���g����̐ڑ��҂�1" << std::endl;

		// �N���C�A���g����̐ڑ�����M����
		dst_socket = accept(src_socket, (struct sockaddr*)&dst_addr, &dst_addr_size);
		
		std::cout << "�N���C�A���g����̐ڑ��L��1" << std::endl;

		snprintf(send_buf, 256, "1");
		// ���ʂ��i�[�����p�P�b�g�̑��M
		send(dst_socket, send_buf, sizeof(char) * 256, 0);
		
		std::cout << "�N���C�A���g����̐ڑ��҂�2" << std::endl;

		dst_socket2 = accept(src_socket, (struct sockaddr*)&dst_addr, &dst_addr_size);

		std::cout << "�N���C�A���g����̐ڑ��L��2" << std::endl;

		snprintf(send_buf, 256, "2");
		// ���ʂ��i�[�����p�P�b�g�̑��M
		send(dst_socket2, send_buf, sizeof(char) * 256, 0);

		//�N���C�A���g�̏W���m�F
		snprintf(send_buf, 256, "�ΐ푊�肪���낢�܂���");
		// ���ʂ��i�[�����p�P�b�g�̑��M
		send(dst_socket, send_buf, sizeof(char) * 256, 0);
		// ���ʂ��i�[�����p�P�b�g�̑��M
		send(dst_socket2, send_buf, sizeof(char) * 256, 0);


		// �ڑ���̏���
		while (1) {

			int status;

			//�N���C�A���g�P����̎�M
			//�p�P�b�g�̎�M(recv�͐�������Ǝ�M�����f�[�^�̃o�C�g����ԋp�B�ؒf��0�A���s��-1���ԋp�����
			int recv1_result = recv(dst_socket, recv_buf1, sizeof(char) * 256, 0);
			if (recv1_result == 0 || recv1_result == -1) {
				status = closesocket(dst_socket); break;
			}
			std::cout << "��M��������1�� : " << recv_buf1 << std::endl;

			/*int recv2_result = recv(dst_socket, recv_buf2, sizeof(char) * 256, 0);
			if (recv2_result == 0 || recv2_result == -1) {
				status = closesocket(dst_socket); break;
			}
			std::cout << "��M��������2�� : " << recv_buf2 << std::endl;*/

			//�N���C�A���g�Q����̎�M
			int recv2_result = recv(dst_socket2, recv_buf2, sizeof(char) * 256, 0);
			if (recv2_result == 0 || recv2_result == -1) {
				status = closesocket(dst_socket2); break;
			}
			std::cout << "��M��������2�� : " << recv_buf2 << std::endl;

			
			// ��M�������������Z

			int num1 = atoi(recv_buf1);
			int num2 = atoi(recv_buf2);

			if (num1 == num2) {
				snprintf(send_buf, 256, "��������");
			}
			else if(num1%3 < num2 % 3){
				snprintf(send_buf, 256, "�N���C�A���g�P�̏���");
			}
			else {
				snprintf(send_buf, 256, "�N���C�A���g�Q�̏���");
			}
			
			// ���ʂ��i�[�����p�P�b�g�̑��M
			send(dst_socket, send_buf, sizeof(char) * 256, 0);
			// ���ʂ��i�[�����p�P�b�g�̑��M
			send(dst_socket2, send_buf, sizeof(char) * 256, 0);
		}
	}

	// WinSock�̏I������
	WSACleanup();

	return 0;
}