{
  "targets": [
    {
      "target_name": "native_test",
      "sources": [
        "index.cpp"
      ],
      "include_dirs": [
        '''<!@(node -p "require('node-addon-api').include")''',
      ],
      "defines": [
        "NAPI_CPP_EXCEPTIONS",
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "conditions": [
        ["OS=='mac'", {
          "cflags+": ["-fvisibility=hidden"],
          "xcode_settings": {
            "GCC_SYMBOLS_PRIVATE_EXTERN": "YES",
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
          }
        }]
      ]
    }
  ]
}
