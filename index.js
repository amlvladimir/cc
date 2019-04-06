const cc = require('./build/Release/cc');
for(let i = 0; i < 10; i++) {
    cc.add(i)
    .then(result => {
        console.log(result);
    })
    .catch(error => console.log(error));
}
