const express = require("express");
const fs = require("fs");

const port = 80;

const server = express();

server.get("*", (req, res)=>{
    try{
        var url = req.url;
        var base_url = url;
        if(base_url.endsWith("/"))
            base_url = base_url.slice(0, -1);
        if(base_url == ""){
            res.redirect("/home");
            return;
        }
        if(base_url == "/home"){
            ReadFile("HomePage.html", res);
            return;
        }

        if(base_url == "/documentation"){
            ReadFile("Documentation/Documentation.html", res);
            return;
        }
        ReadFile(base_url, res);
    }catch(e){}
});

function ReadFile(file_location, res){
    try{
    fs.readFile("src/Website/" + file_location, (error, data)=>{
        var type = GetMimeType(file_location);
        
        const header = {"Content-Type":type}
        if(!error){
            res.writeHead(200, header);
            res.write(data);
        }
        else{
            res.writeHead(404, header);
            res.write("<html><h2>Error 404</h2><h1>Home</h1></html>");
        }
        res.end();
    });
    }catch(e){}
}

function GetMimeType(file_name){
    var array = file_name.split(".");
    //Who knows what file it is
    if(array.length < 2)
        return 'text/html';

    var ext = array[array.length - 1];
    if(ext == "css")return "text/css";
    if(ext == "html")return "text/html";
    if(ext == "js")return "text/javascript";
    return "text/html";
}
server.listen(port, (error, data)=>{
    if(error)
        console.log(`Failed to start server on port ${port}`);
    else
        console.log(`Started server on port ${port}`);
})