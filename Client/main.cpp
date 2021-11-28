#include<iostream>
#include<boost/asio.hpp>
#include<boost/array.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main() {
	try {
		boost::asio::io_service io_service;//(0)통신을 위한 IO Service객체 생성
		tcp::resolver resolver(io_service);//(1)resolver를 통해 도메인 이름을 TCP종단점으로 변환
		tcp::resolver::query query("localhost", "daytime");//(2)DNS서버에 질의문을 보냄(localhost(IP주소)에 daytime프로토콜(13번 포트)로 접속하겠다는 준비)
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);//(3)endpoint객체로 서버와의 연결을 수행
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);//(4)하나의 소캣 객체를 생성하여, 해당 소켓으로 서버와 연결

		while (1) {
			boost::array<char, 128> buf;
			boost::system::error_code error;//버퍼 및 오류 처리 변수 선언
			size_t len = socket.read_some(boost::asio::buffer(buf), error);//(5)버퍼를 이용하여 서버로부터 데이터를 받아옴(read_some)
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);
			cout.write(buf.data(), len);//(6)버퍼에 담긴 데이터를 출력
		}
	}
	catch (exception& e) {
		cerr << e.what() << endl;
	}
	system("pause");
	return 0;
}