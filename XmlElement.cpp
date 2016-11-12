#include "XmlElement.hpp"

#include <iostream>

cgi::xml::XmlElement::XmlElement() : _content("")
{;}

cgi::xml::XmlElement::XmlElement(std::string name) :
		_name(name), _ns("cgi"), _content("")
{;}

cgi::xml::XmlElement::XmlElement(std::string name, std::string ns) :
		_name(name), _ns(ns), _content("")
{;}

cgi::xml::XmlElement::~XmlElement()
{;}

bool cgi::xml::XmlElement::addToXmlElement(xmlpp::Element& parent) const
{
	xmlpp::Element* thisNode = parent.add_child(Glib::ustring(_name),
	                           Glib::ustring(_ns) );
	                           
	if (_content != "") thisNode->set_child_text( Glib::ustring(_content) );
	//DEBUG
	//std::cout << "addToXmlElement:" << _name <<":"<< ":"<<_ns<<std::endl;
	
	for (std::map<std::string, std::string>::const_iterator i = _attribs.begin(); i
	        != _attribs.end(); ++i)
	{
		//DEBUG
		//std::cout << "addToXmlElement_Attrib:" << (*i).first <<":"<< (*i).second <<":"<<_ns<<std::endl;
		
		thisNode->set_attribute(Glib::ustring((*i).first), Glib::ustring((*i).second), Glib::ustring(_ns));
	}
	
	// Render out the children
	for (std::vector< cgi::xml::XmlElement >::const_iterator i = _children.begin(); i
	        != _children.end(); ++i)
	{
		(*i).addToXmlElement(*thisNode);
	}
	
	return true;
}

std::string cgi::xml::XmlElement::getName() const
{
	return _name;
}

std::string cgi::xml::XmlElement::getNameSpaceAlias() const
{
	return _ns;
}

void cgi::xml::XmlElement::setName(const std::string& name)
{
	_name = name;
}

void cgi::xml::XmlElement::setNameSpaceAlias(const std::string& ns)
{
	_ns = ns;
}

void cgi::xml::XmlElement::setAttribute(const std::string& key,
                                        const std::string& value)
{
	_attribs[key] = value;
}

std::string cgi::xml::XmlElement::getAttribute(const std::string& key) const
{
	
	std::map<std::string, std::string>::const_iterator iter =
		_attribs.find(key);
		    
	if (iter == _attribs.end())
	{
		return std::string();
	}
	else
	{
		return iter->second;
	}
}

void cgi::xml::XmlElement::setContent(const std::string& content)
{
	_content = content;
}

std::string cgi::xml::XmlElement::getContent() const
{
	return _content;
}

void cgi::xml::XmlElement::addChildElement(cgi::xml::XmlElement& child)
{
	_children.push_back(child);
}

void cgi::xml::XmlElement::addChildElement(const cgi::xml::XmlElement& child)
{
	_children.push_back(child);
}

const std::vector< cgi::xml::XmlElement >& cgi::xml::XmlElement::getChildren() const
{
	return _children;
}

int cgi::xml::XmlElement::mapElementToDao(xmlpp::Element* xmlpp_element_ptr, cgi::dao::CgiDao& cgidao)
{
	int count = 0;
	const xmlpp::Element::AttributeList& attributes = xmlpp_element_ptr->get_attributes();
	for (xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		const xmlpp::Attribute* attribute = *iter;
		std::string name = attribute->get_name();
		std::string value = attribute->get_value();
		//std::cout << "cgidao.set(" << name << "," << value << ")" << std::endl;
		cgidao.set(name, value);
		++count;
	}
	return count;
}


int cgi::xml::XmlElement::mapElementToMap(xmlpp::Element* xmlpp_element_ptr, std::map< std::string, std::string >& tuple)
{
	int count = 0;
	const xmlpp::Element::AttributeList& attributes = xmlpp_element_ptr->get_attributes();
	for (xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter)
	{
		const xmlpp::Attribute* attribute = *iter;
		std::string name = attribute->get_name();
		std::string value = attribute->get_value();
		cgi::log::MetaLogStream::instance() << cgi::log::Priority::DEBUG << "cgi::xml::XmlElement::mapElementToMap"
		<< "map.set(" << name << "," << value << ")" << cgi::log::flush;

		//std::cout << "cgidao.set(" << name << "," << value << ")" << std::endl;
		tuple[name] = value;
		++count;
	}
	return count;
}

int cgi::xml::XmlElement::mapTupleToElement(const pqxx::tuple& tuple, cgi::xml::XmlElement& xelement)
{
	int attrs_mapped = 0;
	//setAttribute( std::string((*fld).name()), std::string((*fld).c_str())  );
	for (pqxx::tuple::const_iterator fld = tuple.begin(); fld != tuple.end(); ++fld, ++attrs_mapped)
		xelement.setAttribute( fld->name(), fld->c_str() );
	return attrs_mapped;
}

int cgi::xml::XmlElement::mapTupleToElement(const std::map<std::string,std::string>& tuple, cgi::xml::XmlElement& xelement)
{
	int attrs_mapped = 0;
	//setAttribute( std::string((*fld).name()), std::string((*fld).c_str())  );
	for (std::map<std::string,std::string>::const_iterator fld = tuple.begin(); fld != tuple.end(); ++fld, ++attrs_mapped)
		xelement.setAttribute( fld->first, fld->second );
	return attrs_mapped;

}
