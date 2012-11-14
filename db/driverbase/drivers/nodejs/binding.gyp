{
  "targets": [
    {
      "target_name": "djondb",
      "sources": [ "nodeutil.cpp", "djondb.cpp", "wrapconnectionmanager.cpp", "wrapconnection.cpp" ],
      "cflags!": [ "-fno-exceptions"],
      "cflags_cc!": [ "-fno-exceptions"],
		"include_dirs": ["includes"],
		'link_settings': {
         'ldflags': [ '-L/home/cross/workspace/djondb_0.1/db/driverbase/drivers/nodejs/libs'],
         'ldadd': [ '-L/home/cross/workspace/djondb_0.1/db/driverbase/drivers/nodejs/libs'],
			'libraries': [
				'-L/home/cross/workspace/djondb_0.1/db/driverbase/drivers/nodejs/libs -ldjon-client'
				]
		}
	 }
  ]
}
