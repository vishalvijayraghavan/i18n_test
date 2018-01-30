# Text Substitution

This is a python CLI program/tool which has following three commands:

extract-text
- This module will extract all the strings in index.html file and create example.properties(like pot file) which has key(hash of text) and value(actual value) pair content.
- usage: 
    ```shell
    $ python3 text_substitution.py -e
    ```

generate-resource
- This module will generate a language specific properties file(like po files) example.<lang>.
- usage: 
    ```shell
    $ python3 text_substitution.py --generateresource --lang=<lang>
    ```

display-html
- This module will load firefox browser with specified local interface.
- usage: 
    ```shell
    $ python3 text_substitution.py --displayhtml --lang=<lang>
    ```


