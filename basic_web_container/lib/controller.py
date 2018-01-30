
class Controller:

    '''
    This method is to read the html file content
    '''
    def read_file(self,filename):
        with open(filename, 'r') as fp:
            data = fp.read()
        return data

    '''
    This method will choose the right controler and call it
    '''
    def find_routes(self,url,routes):
        if len(url) > 1:
            url = url.replace("/","")
        else:
            url = "/"
        self.routes = routes
        if(url not in self.routes):
            controller_name = self.routes["page_not_found"]['controller']
            view_name = self.routes["page_not_found"]['view']
        else:
            controller_name = self.routes[url]['controller']
            view_name = self.routes[url]['view']
        return getattr(self, controller_name)(view_name)


    def index(self,view):
        html = self.read_file(view)
        return str(html).format(**locals())


    def display(self,view):
        name = "vishal vijayraghavan"
        job = "redhat"
        html = self.read_file(view)
        return str(html).format(**locals())


    def page_not_found(self,view):
        html = self.read_file(view)
        return str(html).format(**locals())