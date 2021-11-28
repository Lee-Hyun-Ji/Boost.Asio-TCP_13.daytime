#include<iostream>
#include<boost/asio.hpp>
#include<boost/array.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
	try {
		boost::asio::io_service io_service;//(0)����� ���� IO Service��ü ����
		tcp::resolver resolver(io_service);//(1)resolver�� ���� ������ �̸��� TCP���������� ��ȯ
		tcp::resolver::query query("localhost", "daytime");//(2)DNS������ ���ǹ��� ����(localhost(IP�ּ�)�� daytime��������(13�� ��Ʈ)�� �����ϰڴٴ� �غ�)
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);//(3)endpoint��ü�� �������� ������ ����
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);//(4)�ϳ��� ��Ĺ ��ü�� �����Ͽ�, �ش� �������� ������ ����

		while (1) {
			boost::array<char, 128> buf;
			boost::system::error_code error;//���� �� ���� ó�� ���� ����
			size_t len = socket.read_some(boost::asio::buffer(buf), error);//(5)���۸� �̿��Ͽ� �����κ��� �����͸� �޾ƿ�(read_some)
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);
			cout.write(buf.data(), len);//(6)���ۿ� ��� �����͸� ���
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}