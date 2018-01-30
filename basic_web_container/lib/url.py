class Url:

    '''
    This method only has the url and their controllers and views.
    '''
    def get_routes(self):

        return {
                    "display":{
                        "controller":"display",
                        "view":"display.html"
                    },
                    '/':{
                        "controller": "index",
                        "view": "index.html"
                    },
                    'page_not_found':{
                        "controller": "page_not_found",
                        "view": "page_not_found.html"
                    }
                }