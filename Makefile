.PHONY: clear clean configure build install start
build:
	node-gyp rebuild
start:
	npm start
install:
	npm install
configure:
	node-gyp configure
clear:
	node-gyp clean
clean: clear
