from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import urlparse
from sys import argv
import lib

class S(BaseHTTPRequestHandler,lib.Controller,lib.Url):
    '''
    Http headers
    '''
    def _set_headers(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
    '''
    This method will capture all the get request made on server.
    '''
    def do_GET(self):
        parsed_path = urlparse(self.path)
        self.path = parsed_path.path
        self.routes = self.get_routes()
        data = self.find_routes(self.path,self.routes)
        self._set_headers()
        self.wfile.write(bytes(data,'ascii'))

    '''
    This method will set the http packet header.
    '''
    def do_HEAD(self):
        self._set_headers()

    '''
    This method will capture all the post request made on server
    '''
    def do_POST(self):
        self._set_headers()
        self.wfile.write("<html><body><h1>No api for now, working on the same...</h1></body></html>")

'''
This method will start http server on specified port
'''
def run(server_class=HTTPServer, handler_class=S, port=8000):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print('Starting httpd @ localhost:'+str(port)+'...')
    httpd.serve_forever()


if __name__ == "__main__":

    if len(argv) == 2:
        run(port=int(argv[1].split(":")[1]))
    elif len(argv) == 3:
        run(port=int(argv[2].split(":")[1]))
    else:
        run()