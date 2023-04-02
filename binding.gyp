{
  "targets": [
    {
			"target_name": "addon_pdjs",
			"cflags!": [ "-fno-exceptions" ],
			"cflags_cc!": [ "-fno-exceptions" ],
			"sources": [ "addon_pdjs.cc" ],
			"include_dirs": [
				"<!@(node -p \"require('node-addon-api').include\")"
			],
			'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
		}
  ]
}
