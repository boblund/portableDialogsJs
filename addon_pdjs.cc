#include <napi.h>
#include "portable-file-dialogs.h"

#include <string>
#include <iostream>

using namespace std;

Napi::Value SaveFile(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() > 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

	string arg0 = info[0].As<Napi::String>();

  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Argument not string").ThrowAsJavaScriptException();
    return env.Null();
  }

	return Napi::String::New(env, pfd::save_file("Choose file to save", arg0,
                            { "Text Files (.txt .text)", "*.txt *.text" },
                            pfd::opt::force_overwrite).result());
}

Napi::Value OpenFile(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
    return env.Null();
  }

  string arg0 = info[0].As<Napi::String>();

  auto f = pfd::open_file("Choose files to read", arg0,
                            { "Text Files (.txt .text)", "*.txt *.text",
                              "All Files", "*" },
                            pfd::opt::multiselect);
	std::string out = "";
	for(auto& it:f.result()) {out += it;}
	return Napi::String::New(env, out);
}

Napi::Value Message(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  for(int i = 0; i<3; i++) {
		if (!info[i].IsString()) {
			Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
			return env.Null();
		}
  }

  string title = info[0].As<Napi::String>();
	string msg = info[1].As<Napi::String>();
	string msgType = info[2].As<Napi::String>();

	pfd::icon _icon = (msgType == "info")
	? pfd::icon::info : (msgType == "warning")
		? pfd::icon::warning : (msgType == "question")
			? pfd::icon::question : pfd::icon::error;

	auto m = pfd::message(title, msg, pfd::choice::yes_no_cancel, _icon);

	// Do something according to the selected button
	switch (m.result())
	{
			case pfd::button::yes: return Napi::String::New(env, "yes"); break;
			case pfd::button::no: return Napi::String::New(env, "no"); break;
			case pfd::button::cancel: return Napi::String::New(env, "cancel"); break;
			default: return Napi::String::New(env, "error"); break; // Should not happen
	}
}

Napi::Value Notify(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  for(int i = 0; i<3; i++) {
		if (!info[i].IsString()) {
			Napi::TypeError::New(env, "Wrong arguments").ThrowAsJavaScriptException();
			return env.Null();
		}
  }

  string title = info[0].As<Napi::String>();
	string msg = info[1].As<Napi::String>();
	string msgType = info[2].As<Napi::String>();

	pfd::icon _icon = (msgType == "info")
	? pfd::icon::info : (msgType == "warning")
		? pfd::icon::warning : (msgType == "question")
			? pfd::icon::question : pfd::icon::error;

	pfd::notify(title, msg, _icon);

	return env.Null();

}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("save_file", Napi::Function::New(env, SaveFile));
	exports.Set("open_file", Napi::Function::New(env, OpenFile));
	exports.Set("message", Napi::Function::New(env, Message));
	exports.Set("notify", Napi::Function::New(env, Notify));
  return exports;
}

NODE_API_MODULE(addon_pfd, Init)
