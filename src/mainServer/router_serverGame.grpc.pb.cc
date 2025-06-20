// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: router_serverGame.proto

#include "router_serverGame.pb.h"
#include "router_serverGame.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace router_serverGame {

static const char* ServerGame_method_names[] = {
  "/router_serverGame.ServerGame/StartNewGame",
  "/router_serverGame.ServerGame/AddCommandGame",
  "/router_serverGame.ServerGame/StopGame",
  "/router_serverGame.ServerGame/LogGame",
};

std::unique_ptr< ServerGame::Stub> ServerGame::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< ServerGame::Stub> stub(new ServerGame::Stub(channel, options));
  return stub;
}

ServerGame::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_StartNewGame_(ServerGame_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_AddCommandGame_(ServerGame_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_StopGame_(ServerGame_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_LogGame_(ServerGame_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status ServerGame::Stub::StartNewGame(::grpc::ClientContext* context, const ::router_serverGame::StartNewGameRequest& request, ::router_serverGame::StartNewGameReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::router_serverGame::StartNewGameRequest, ::router_serverGame::StartNewGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_StartNewGame_, context, request, response);
}

void ServerGame::Stub::async::StartNewGame(::grpc::ClientContext* context, const ::router_serverGame::StartNewGameRequest* request, ::router_serverGame::StartNewGameReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::router_serverGame::StartNewGameRequest, ::router_serverGame::StartNewGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_StartNewGame_, context, request, response, std::move(f));
}

void ServerGame::Stub::async::StartNewGame(::grpc::ClientContext* context, const ::router_serverGame::StartNewGameRequest* request, ::router_serverGame::StartNewGameReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_StartNewGame_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::router_serverGame::StartNewGameReply>* ServerGame::Stub::PrepareAsyncStartNewGameRaw(::grpc::ClientContext* context, const ::router_serverGame::StartNewGameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::router_serverGame::StartNewGameReply, ::router_serverGame::StartNewGameRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_StartNewGame_, context, request);
}

::grpc::ClientAsyncResponseReader< ::router_serverGame::StartNewGameReply>* ServerGame::Stub::AsyncStartNewGameRaw(::grpc::ClientContext* context, const ::router_serverGame::StartNewGameRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncStartNewGameRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ServerGame::Stub::AddCommandGame(::grpc::ClientContext* context, const ::router_serverGame::AddCommandGameRequest& request, ::router_serverGame::AddCommandGameReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::router_serverGame::AddCommandGameRequest, ::router_serverGame::AddCommandGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_AddCommandGame_, context, request, response);
}

void ServerGame::Stub::async::AddCommandGame(::grpc::ClientContext* context, const ::router_serverGame::AddCommandGameRequest* request, ::router_serverGame::AddCommandGameReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::router_serverGame::AddCommandGameRequest, ::router_serverGame::AddCommandGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddCommandGame_, context, request, response, std::move(f));
}

void ServerGame::Stub::async::AddCommandGame(::grpc::ClientContext* context, const ::router_serverGame::AddCommandGameRequest* request, ::router_serverGame::AddCommandGameReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AddCommandGame_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::router_serverGame::AddCommandGameReply>* ServerGame::Stub::PrepareAsyncAddCommandGameRaw(::grpc::ClientContext* context, const ::router_serverGame::AddCommandGameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::router_serverGame::AddCommandGameReply, ::router_serverGame::AddCommandGameRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_AddCommandGame_, context, request);
}

::grpc::ClientAsyncResponseReader< ::router_serverGame::AddCommandGameReply>* ServerGame::Stub::AsyncAddCommandGameRaw(::grpc::ClientContext* context, const ::router_serverGame::AddCommandGameRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncAddCommandGameRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ServerGame::Stub::StopGame(::grpc::ClientContext* context, const ::router_serverGame::StopGameRequest& request, ::router_serverGame::StopGameReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::router_serverGame::StopGameRequest, ::router_serverGame::StopGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_StopGame_, context, request, response);
}

void ServerGame::Stub::async::StopGame(::grpc::ClientContext* context, const ::router_serverGame::StopGameRequest* request, ::router_serverGame::StopGameReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::router_serverGame::StopGameRequest, ::router_serverGame::StopGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_StopGame_, context, request, response, std::move(f));
}

void ServerGame::Stub::async::StopGame(::grpc::ClientContext* context, const ::router_serverGame::StopGameRequest* request, ::router_serverGame::StopGameReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_StopGame_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::router_serverGame::StopGameReply>* ServerGame::Stub::PrepareAsyncStopGameRaw(::grpc::ClientContext* context, const ::router_serverGame::StopGameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::router_serverGame::StopGameReply, ::router_serverGame::StopGameRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_StopGame_, context, request);
}

::grpc::ClientAsyncResponseReader< ::router_serverGame::StopGameReply>* ServerGame::Stub::AsyncStopGameRaw(::grpc::ClientContext* context, const ::router_serverGame::StopGameRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncStopGameRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status ServerGame::Stub::LogGame(::grpc::ClientContext* context, const ::router_serverGame::LogGameRequest& request, ::router_serverGame::LogGameReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::router_serverGame::LogGameRequest, ::router_serverGame::LogGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_LogGame_, context, request, response);
}

void ServerGame::Stub::async::LogGame(::grpc::ClientContext* context, const ::router_serverGame::LogGameRequest* request, ::router_serverGame::LogGameReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::router_serverGame::LogGameRequest, ::router_serverGame::LogGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_LogGame_, context, request, response, std::move(f));
}

void ServerGame::Stub::async::LogGame(::grpc::ClientContext* context, const ::router_serverGame::LogGameRequest* request, ::router_serverGame::LogGameReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_LogGame_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::router_serverGame::LogGameReply>* ServerGame::Stub::PrepareAsyncLogGameRaw(::grpc::ClientContext* context, const ::router_serverGame::LogGameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::router_serverGame::LogGameReply, ::router_serverGame::LogGameRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_LogGame_, context, request);
}

::grpc::ClientAsyncResponseReader< ::router_serverGame::LogGameReply>* ServerGame::Stub::AsyncLogGameRaw(::grpc::ClientContext* context, const ::router_serverGame::LogGameRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncLogGameRaw(context, request, cq);
  result->StartCall();
  return result;
}

ServerGame::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ServerGame_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ServerGame::Service, ::router_serverGame::StartNewGameRequest, ::router_serverGame::StartNewGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ServerGame::Service* service,
             ::grpc::ServerContext* ctx,
             const ::router_serverGame::StartNewGameRequest* req,
             ::router_serverGame::StartNewGameReply* resp) {
               return service->StartNewGame(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ServerGame_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ServerGame::Service, ::router_serverGame::AddCommandGameRequest, ::router_serverGame::AddCommandGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ServerGame::Service* service,
             ::grpc::ServerContext* ctx,
             const ::router_serverGame::AddCommandGameRequest* req,
             ::router_serverGame::AddCommandGameReply* resp) {
               return service->AddCommandGame(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ServerGame_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ServerGame::Service, ::router_serverGame::StopGameRequest, ::router_serverGame::StopGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ServerGame::Service* service,
             ::grpc::ServerContext* ctx,
             const ::router_serverGame::StopGameRequest* req,
             ::router_serverGame::StopGameReply* resp) {
               return service->StopGame(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      ServerGame_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< ServerGame::Service, ::router_serverGame::LogGameRequest, ::router_serverGame::LogGameReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](ServerGame::Service* service,
             ::grpc::ServerContext* ctx,
             const ::router_serverGame::LogGameRequest* req,
             ::router_serverGame::LogGameReply* resp) {
               return service->LogGame(ctx, req, resp);
             }, this)));
}

ServerGame::Service::~Service() {
}

::grpc::Status ServerGame::Service::StartNewGame(::grpc::ServerContext* context, const ::router_serverGame::StartNewGameRequest* request, ::router_serverGame::StartNewGameReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ServerGame::Service::AddCommandGame(::grpc::ServerContext* context, const ::router_serverGame::AddCommandGameRequest* request, ::router_serverGame::AddCommandGameReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ServerGame::Service::StopGame(::grpc::ServerContext* context, const ::router_serverGame::StopGameRequest* request, ::router_serverGame::StopGameReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status ServerGame::Service::LogGame(::grpc::ServerContext* context, const ::router_serverGame::LogGameRequest* request, ::router_serverGame::LogGameReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace router_serverGame

