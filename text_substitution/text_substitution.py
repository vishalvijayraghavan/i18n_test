from lxml import etree
import hashlib
import os
import json
import argparse


class Text_Substitution:
    def __init__(self):
        self.resource_path = "./resource/"
        self.resource_name = "example"
        if not os.path.isdir(self.resource_path):
            os.makedirs(self.resource_path)

    '''
    md5 hash generator 
    '''
    def md5_hash(self,text):
        return hashlib.md5(text.encode()).hexdigest()

    '''
    create a property file via dict
    '''
    def json_dump(self, filepath, data):
        with open(filepath, 'w') as fp:
            json.dump(data, fp)
    '''
    read property file into dict
    '''
    def json_load(self,filepath):
        with open(filepath) as fp:
            data = json.load(fp)
        return data

    '''
    This function will parse entire html page and make list of all strings and create a .properties file
    with key(string hash) and value(string) pair
    '''
    def parse_html(self):
        parser = etree.HTMLParser()
        tree = etree.parse('index.html', parser)
        text_list = tree.xpath("//body//*[not(self::script) and not(self::noscript)]/text()")
        text_list = [x.strip() for x in text_list if x.strip()]
        text_dict = dict()
        for text in text_list:
            text_dict[self.md5_hash(text)] = text
        self.json_dump(filepath=self.resource_path+self.resource_name+".properties",data=text_dict)

    '''
    This function will generate a portable object file 
    '''
    def generate_resource(self,lang):
        resource_json = self.json_load(self.resource_path+self.resource_name+".properties")
        new_resource_json = dict()
        for key,value in resource_json.items():
            new_resource_json[key] = ""
        self.json_dump(filepath=self.resource_path+self.resource_name+"."+lang,data=new_resource_json)

    '''
    This method is used to read the html file string
    '''
    def read_file(self,filename):
        with open(filename, 'r') as fp:
            data = fp.read()
        return data

    '''
    This method is used to write the updated html file string.
    '''
    def write_file(self,filename,data):
        with open(filename, 'w') as fp:
            fp.write(data)

    '''
    This function will open the pot(example.property) and po(exmpale.dutch) file.
    Update the provided locale on translate_index.html and open in firefox browser 
    '''
    def display_html(self,lang):
        if lang == 'en_us':
            os.system("firefox index.html")
        else:
            if os.path.isfile(self.resource_path+self.resource_name+"."+lang):
                pot = self.json_load(self.resource_path+self.resource_name+".properties")
                po = self.json_load(self.resource_path+self.resource_name+"."+lang)
                html_string = self.read_file("index.html")
                for key,value in pot.items():
                    html_string = html_string.replace(pot[key], po[key])
                self.write_file("translated_index.html",html_string)
                os.system("firefox translated_index.html")
            else:
                print("invalid locale provided")

if __name__ == "__main__":


    parser = argparse.ArgumentParser(description="html i18n parser")
    parser.add_argument("-e","--extracttext",help="extarct text and generate pot",action="store_true")
    parser.add_argument("-r", "--generateresource", help="generate portable object files", action="store_true")
    parser.add_argument("-l","--lang",help="specify the locale",default='en_us')
    parser.add_argument("-d", "--displayhtml", help="display html in specific locale",action="store_true")
    args = parser.parse_args()

    obj = Text_Substitution()

    if args.extracttext:
        obj.parse_html()
    elif args.generateresource:
        if not args.lang:
            print("please use --lang parameter")
            parser.print_help()
        else:
            obj.generate_resource(lang=args.lang)
    elif args.displayhtml:
        if not args.lang:
            print("please use --lang parameter")
            parser.print_help()
        else:
            obj.display_html(lang=args.lang)
    else:
        parser.print_help()