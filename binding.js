const cc;
if (process.env.DEBUG) {
	cc = require('./build/Debug/cc.node');
} else {
	cc = require('./build/Release/cc.node');
}
module.exports = cc;
