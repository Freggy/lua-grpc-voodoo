extern "C" 
{
	#include <lua5.3/lualib.h>
    	#include <lua5.3/lauxlib.h>
    	#include <lua5.3/lua.h>
}

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "helloworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;

class GreeterClient {
 	public:
  		GreeterClient(std::shared_ptr<Channel> channel) : stub_(Greeter::NewStub(channel)) {}

	// Assembles the client's payload, sends it and presents the response back
  	// from the server.
  	std::string SayHello(const std::string& user) {
    		// Data we are sending to the server.
    		HelloRequest request;
    		request.set_name(user);

    		// Container for the data we expect from the server.
    		HelloReply reply;

    		// Context for the client. It could be used to convey extra information to
    		// the server and/or tweak certain RPC behaviors.
    		ClientContext context;

    		// The actual RPC.
    		Status status = stub_->SayHello(&context, request, &reply);

    		// Act upon its status.
    		if (status.ok()) {
      			return reply.message();
    		} else {
      			std::cout << status.error_code() << ": " << status.error_message() << std::endl;
      			return "RPC failed";
    		}
  	}
	private:
  		std::unique_ptr<Greeter::Stub> stub_;
};


int greet(lua_State* L)
{
	GreeterClient greeter(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  	std::string user("world");
  	std::string reply = greeter.SayHello(user);
	std::cout << reply << std::endl;
    	return 0;
}

static const luaL_Reg funcs[] =
{
	{ "greet", greet},
    	{ NULL, NULL }
};

extern "C" int luaopen_lib(lua_State* L) 
{
	luaL_newlibtable(L, funcs);
	luaL_setfuncs(L, funcs, 0);
    	return 1;
}
