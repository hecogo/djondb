{
  "targets": [
    {
      "target_name": "djondb",
      "sources": [ "nodeutil.cpp", "djondb.cpp", "wrapconnectionmanager.cpp", "wrapconnection.cpp" ],
      "cflags!": [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-exceptions"],
		"include_dirs": [".."],
		'link_settings': {
			'libraries': [
				'-ldjon-client'
				]
		}
	 }
  ]
}
