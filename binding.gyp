{
    "targets": [
        {
            "target_name": "cc",
            "sources": [ "source/Main.cc", "source/AddonData.cc", "source/PromiseWorker.cc" ],
            "include_dirs": [
                #"/usr/local/include",
                "<!(node -e \"require('nan')\")"
            ],
            "cflags!": [ "-fno-exceptions", "-fno-rtti" ],
            "cflags": [ "-std=c++17", "-g", "-W", "-frtti" ],
            "cflags_cc": [ "-std=c++17" ],
            "cflags_cc!": [ "-fno-exceptions", "-fno-rtti" ],
            "libraries": [
                #"-L /usr/local/lib /usr/local/lib/*.so /usr/local/lib/*.so.*",
                ]
        }
    ]
}
