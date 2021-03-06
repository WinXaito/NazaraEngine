#include <Nazara/Network/SocketPoller.hpp>
#include <Nazara/Network/TcpClient.hpp>
#include <Nazara/Network/TcpServer.hpp>
#include <Catch/catch.hpp>

#include <Nazara/Math/Vector3.hpp>
#include <Nazara/Network/NetPacket.hpp>

SCENARIO("SocketPoller", "[NETWORK][SOCKETPOLLER]")
{
	GIVEN("A TcpServer and a TcpClient in a selector")
	{
		Nz::UInt16 port = 64256;
		Nz::TcpServer server;
		server.EnableBlocking(false);

		REQUIRE(server.Listen(Nz::NetProtocol_IPv4, port) == Nz::SocketState_Bound);

		Nz::IpAddress serverIP(Nz::IpAddress::LoopbackIpV4.ToIPv4(), port);
		REQUIRE(serverIP.IsValid());

		Nz::SocketPoller serverPoller;
		Nz::TcpClient clientToServer;

		WHEN("We register the server socket to the poller")
		{
			REQUIRE(serverPoller.RegisterSocket(server));

			THEN("The poller should have registered our socket")
			{
				REQUIRE(serverPoller.IsRegistered(server));
			}
			AND_THEN("We connect using a TcpClient")
			{
				Nz::SocketState state = clientToServer.Connect(serverIP);

				REQUIRE(state != Nz::SocketState_NotConnected);

				AND_THEN("We wait on our selector, it should return true")
				{
					REQUIRE(serverPoller.Wait(1000));

					Nz::TcpClient serverToClient;
					REQUIRE(server.AcceptClient(&serverToClient));

					WHEN("We register the client socket to the poller")
					{
						REQUIRE(serverPoller.RegisterSocket(serverToClient));

						THEN("The poller should have registered our socket")
						{
							REQUIRE(serverPoller.IsRegistered(serverToClient));
						}

						AND_WHEN("We test sending data from the client to the server and checking the poller")
						{
							std::array<char, 5> buffer = {"Data"};

							std::size_t sent;
							REQUIRE(clientToServer.Send(buffer.data(), buffer.size(), &sent));
							REQUIRE(sent == buffer.size());

							REQUIRE(serverPoller.Wait(1000));

							REQUIRE(serverPoller.IsReady(serverToClient));

							REQUIRE(serverToClient.Read(buffer.data(), buffer.size()) == sent);

							AND_THEN("Our selector should report no socket ready")
							{
								REQUIRE(!serverPoller.Wait(100));

								REQUIRE(!serverPoller.IsReady(serverToClient));
							}
						}
					}
				}
			}
		}
 	}
}
