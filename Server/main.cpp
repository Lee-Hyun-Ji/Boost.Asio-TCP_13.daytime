#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include<string>
#include<boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

string make_daytime_string() {
	time_t now = time(0);//�ð����� �ʱ�ȭ('time_t'�� time()�Լ��� ��ȯ��)
	return ctime(&now);//���ڿ� ���·� ���� ��ǻ���� ��¥ �� �ð����� ��ȯ
}

int main()
{
	try {
		boost::asio::io_service io_service;//(0)IO Service ��ü ����
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));//(1)13�� ��Ʈ�� ����޴� ���� ���� ����
		while (1)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);//(2)Ŭ���̾�Ʈ ���� ���� ��, ������ ��ٸ�
			string message = make_daytime_string();//make_daytime_string()�Լ��� �̿��� ���� �޽��� ����
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);//(3)�޽����� ���ۿ� ��� ����
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
	return 0;
}