//
// Created by Nikolai on 04.11.2021.
//

#ifndef ARDUINOPROJECT_WEBWRAPPERTEMPLATE_HPP
#define ARDUINOPROJECT_WEBWRAPPERTEMPLATE_HPP

class WebWrapperTemplate {
protected:
    char* templateOfWebPage = 0;
    int length = 0;
    int size = 0;
    int type = 0;
public:
    WebWrapperTemplate(char *templateOfWebPage)
    {
        length = strlen(templateOfWebPage);
        this->templateOfWebPage = new char[length + 1];
        memset(this->templateOfWebPage, 0, sizeof(char) * (length + 1));
        memcpy(this->templateOfWebPage, templateOfWebPage, length);
    }
    int getLength(){
        return length;
    }
    char* getTemplateOfWebPage()
    {
        return templateOfWebPage;
    }
    ~WebWrapperTemplate()
    {
        delete templateOfWebPage;
    }
};

#endif //ARDUINOPROJECT_WEBWRAPPERTEMPLATE_HPP
