rm -rf djondb.app
mkdir -p djondb.app/Contents/Frameworks
mkdir -p djondb.app/Contents/MacOS

cp /usr/lib/libdjon-util.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libdjon-cache.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libdjon-client.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libdjon-command.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libdjon-db.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libdjon-filesystem.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libdjon-network.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libdjon-service.0.dylib djondb.app/Contents/Frameworks/
cp /usr/lib/libv8.dylib djondb.app/Contents/Frameworks/
cp /usr/bin/djondbd djondb.app/Contents/MacOS
cp /usr/bin/djon-shell djondb.app/Contents/MacOS


install_name_tool -id @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libdjon-client.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libdjon-command.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libdjon-db.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libdjon-filesystem.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libdjon-network.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libdjon-service.0.dylib djondb.app/Contents/Frameworks/libdjon-util.0.dylib
install_name_tool -id @executable_path/../Frameworks/libv8.dylib djondb.app/Contents/Frameworks/libv8.dylib

# change of bson
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-bson.0.dylib

# change of cache
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-cache.0.dylib
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/libdjon-cache.0.dylib

# change of filesystem
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-filesystem.0.dylib
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/libdjon-filesystem.0.dylib
install_name_tool -change libdjon-cache.0.dylib @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/Frameworks/libdjon-filesystem.0.dylib

# change of db
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-db.0.dylib
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/libdjon-db.0.dylib
install_name_tool -change libdjon-cache.0.dylib @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/Frameworks/libdjon-db.0.dylib
install_name_tool -change libdjon-filesystem.0.dylib @executable_path/../Frameworks/libdjon-filesystem.0.dylib djondb.app/Contents/Frameworks/libdjon-db.0.dylib

# change of command
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-command.0.dylib
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/libdjon-command.0.dylib
install_name_tool -change libdjon-cache.0.dylib @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/Frameworks/libdjon-command.0.dylib
install_name_tool -change libdjon-filesystem.0.dylib @executable_path/../Frameworks/libdjon-filesystem.0.dylib djondb.app/Contents/Frameworks/libdjon-command.0.dylib
install_name_tool -change libdjon-db.0.dylib @executable_path/../Frameworks/libdjon-db.0.dylib djondb.app/Contents/Frameworks/libdjon-command.0.dylib

# change of network
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-network.0.dylib
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/libdjon-network.0.dylib
install_name_tool -change libdjon-cache.0.dylib @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/Frameworks/libdjon-network.0.dylib
install_name_tool -change libdjon-filesystem.0.dylib @executable_path/../Frameworks/libdjon-filesystem.0.dylib djondb.app/Contents/Frameworks/libdjon-network.0.dylib
install_name_tool -change libdjon-db.0.dylib @executable_path/../Frameworks/libdjon-db.0.dylib djondb.app/Contents/Frameworks/libdjon-network.0.dylib
install_name_tool -change libdjon-command.0.dylib @executable_path/../Frameworks/libdjon-command.0.dylib djondb.app/Contents/Frameworks/libdjon-network.0.dylib

# change of driverbase
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-client.0.dylib
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/libdjon-client.0.dylib
install_name_tool -change libdjon-cache.0.dylib @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/Frameworks/libdjon-client.0.dylib
install_name_tool -change libdjon-filesystem.0.dylib @executable_path/../Frameworks/libdjon-filesystem.0.dylib djondb.app/Contents/Frameworks/libdjon-client.0.dylib
install_name_tool -change libdjon-db.0.dylib @executable_path/../Frameworks/libdjon-db.0.dylib djondb.app/Contents/Frameworks/libdjon-client.0.dylib
install_name_tool -change libdjon-command.0.dylib @executable_path/../Frameworks/libdjon-command.0.dylib djondb.app/Contents/Frameworks/libdjon-client.0.dylib
install_name_tool -change libdjon-network.0.dylib @executable_path/../Frameworks/libdjon-network.0.dylib djondb.app/Contents/Frameworks/libdjon-client.0.dylib

# change of service
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/Frameworks/libdjon-service.0.dylib
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/Frameworks/libdjon-service.0.dylib
install_name_tool -change libdjon-cache.0.dylib @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/Frameworks/libdjon-service.0.dylib
install_name_tool -change libdjon-filesystem.0.dylib @executable_path/../Frameworks/libdjon-filesystem.0.dylib djondb.app/Contents/Frameworks/libdjon-service.0.dylib
install_name_tool -change libdjon-db.0.dylib @executable_path/../Frameworks/libdjon-db.0.dylib djondb.app/Contents/Frameworks/libdjon-service.0.dylib
install_name_tool -change libdjon-command.0.dylib @executable_path/../Frameworks/libdjon-command.0.dylib djondb.app/Contents/Frameworks/libdjon-service.0.dylib
install_name_tool -change libdjon-network.0.dylib @executable_path/../Frameworks/libdjon-network.0.dylib djondb.app/Contents/Frameworks/libdjon-service.0.dylib

# change of djondbd
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/MacOS/djondbd
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/MacOS/djondbd
install_name_tool -change libdjon-cache.0.dylib @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/MacOS/djondbd
install_name_tool -change libdjon-filesystem.0.dylib @executable_path/../Frameworks/libdjon-filesystem.0.dylib djondb.app/Contents/MacOS/djondbd
install_name_tool -change libdjon-db.0.dylib @executable_path/../Frameworks/libdjon-db.0.dylib djondb.app/Contents/MacOS/djondbd
install_name_tool -change libdjon-command.0.dylib @executable_path/../Frameworks/libdjon-command.0.dylib djondb.app/Contents/MacOS/djondbd
install_name_tool -change libdjon-network.0.dylib @executable_path/../Frameworks/libdjon-network.0.dylib djondb.app/Contents/MacOS/djondbd
install_name_tool -change libdjon-client.0.dylib @executable_path/../Frameworks/libdjon-client.0.dylib djondb.app/Contents/MacOS/djondbd

# change of djon-shell
install_name_tool -change libdjon-util.0.dylib @executable_path/../Frameworks/libdjon-util.0.dylib djondb.app/Contents/MacOS/djon-shell
install_name_tool -change libdjon-bson.0.dylib @executable_path/../Frameworks/libdjon-bson.0.dylib djondb.app/Contents/MacOS/djon-shell
install_name_tool -change libdjon-cache.0.dylib @executable_path/../Frameworks/libdjon-cache.0.dylib djondb.app/Contents/MacOS/djon-shell
install_name_tool -change libdjon-filesystem.0.dylib @executable_path/../Frameworks/libdjon-filesystem.0.dylib djondb.app/Contents/MacOS/djon-shell
install_name_tool -change libdjon-db.0.dylib @executable_path/../Frameworks/libdjon-db.0.dylib djondb.app/Contents/MacOS/djon-shell
install_name_tool -change libdjon-command.0.dylib @executable_path/../Frameworks/libdjon-command.0.dylib djondb.app/Contents/MacOS/djon-shell
install_name_tool -change libdjon-network.0.dylib @executable_path/../Frameworks/libdjon-network.0.dylib djondb.app/Contents/MacOS/djon-shell
install_name_tool -change libdjon-client.0.dylib @executable_path/../Frameworks/libdjon-client.0.dylib djondb.app/Contents/MacOS/djon-shell
install_name_tool -change libv8.dylib @executable_path/../Frameworks/libv8.dylib djondb.app/Contents/MacOS/djon-shell

# macdeployqt djondb.app -dmg
hdiutil create -fs HFS+ -volname djondb 0.1 -srcfolder djondb.app djondb.dmg
