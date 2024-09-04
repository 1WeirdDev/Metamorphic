const https = require('node:https');
const fs = require('node:fs');
    
const httpsOptions = {
    key : fs.readFileSync('path/to/server-key.pem'),
    cert : fs.readFileSync('path/to/server-crt.pem')
};

const app = function (req, res) {
    res.writeHead(200);
    res.end("hello world\n");
}
    
https.createServer(httpsOptions, app).listen(4433);

const options = {
  key : fs.readFileSync('test/fixtures/keys/agent2-key.pem'),
  cert : fs.readFileSync('test/fixtures/keys/agent2-cert.pem'),
};