var addon = require('./build/Release/djondb');

var manager = new addon.WrapConnectionManager();
manager.getConnection("localhost");

