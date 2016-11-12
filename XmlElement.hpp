#ifndef _CGI_XMLELEMENT_H_
#define _CGI_XMLELEMENT_H_

#include <string>
#include <vector>
#include <map>

#include <libxml++/libxml++.h>
#include <pqxx/pqxx>

#include <cgi/dao/CgiDao.hpp>

namespace cgi
{

///
/// The cgi::xml namespace contains all classes and functions
/// related to the use of the CGI Application and Web Services.
///
/// \brief Application/Web Service namespace
///
namespace xml
{

///
/// CGI General Data Access Object
///
class XmlElement
{

	public:
	
		///
		/// Constructor for the General XML Element
		///
		///
		XmlElement();
		
		///
		/// Overload Constructor for the General Data Access Object
		///
		/// \param name Element name in the XML Structure, e.g. type
		///
		XmlElement(std::string name);
		
		///
		/// Overload Constructor for the General Data Access Object
		///
		/// \param name Element name in the XML Structure, e.g. type
		/// \param ns Namespace alias of this element
		///
		XmlElement(std::string name, std::string ns);
		
		///
		/// Destructor for the General Data Access Object
		///
		virtual ~XmlElement();
		
		///
		/// add this element to a parent XML Element
		///
		/// \param parent The parent node that this will render into
		///
		virtual bool addToXmlElement(xmlpp::Element& parent) const;
		
		///
		/// Get the Name of this element,
		///
		virtual std::string getName() const;
		
		///
		/// Get the NameSpace alias of this element,
		///
		virtual std::string getNameSpaceAlias() const;
		
		///
		/// Set the Name of this element
		///
		virtual void setName(const std::string& name);
		
		///
		/// Set the NameSpace of this element
		///
		virtual void setNameSpaceAlias(const std::string& ns);
		
		///
		/// Set Attribute
		///
		virtual void setAttribute(const std::string& key, const std::string& value);
		
		///
		/// Get Attribute
		///
		virtual std::string getAttribute(const std::string& key) const;
		
		///
		/// Set Element Content to Text
		///
		virtual void setContent(const std::string& content);
		
		///
		/// Get Element Content to Text
		///
		virtual std::string getContent() const;
		
		///
		/// Add child element to this element
		///
		/// \param child The child XmlElement to be added
		///
		void addChildElement(cgi::xml::XmlElement& child);
		
		///
		/// Add child element to this element
		///
		/// \param child The child XmlElement to be added
		///
		void addChildElement(const cgi::xml::XmlElement& child);
		
		///
		/// Decompose an XML++ Element from DOM parsing into an DAO's attribute map
		///
		/// \param xmlpp_element_ptr Reference to an XML DOM Element
		/// \param cgidao Reference to a CgiDao derived class
		///
		/// \returns number of attributes
		static int mapElementToDao(xmlpp::Element* xmlpp_element_ptr, cgi::dao::CgiDao& cgidao);
		
		
		///
		/// Decompose an XML++ Element from DOM parsing into an attribute map
		///
		/// \param xmlpp_element_ptr Reference to an XML DOM Element
		/// \param tuple Map of Name, Value
		///
		/// \returns number of attributes
		static int mapElementToMap(xmlpp::Element* xmlpp_element_ptr, std::map< std::string, std::string >& tuple);
		
		///
		/// Decompose a pqxx Tuple into an XML++ Elements Attributes
		///
		/// \param tuple pqxx tuple (result row)
		/// \param xelement The XmlElement to recieve the attributes
		///
		/// \returns number of attributes mapped into the XmlElement
		static int mapTupleToElement(const pqxx::tuple& tuple, cgi::xml::XmlElement& xelement);
		
		///
		/// Decompose a std::map<string,string> Tuple into an XML++ Elements Attributes
		///
		/// \param tuple std::map<string,string>  tuple
		/// \param xelement The XmlElement to recieve the attributes
		///
		/// \returns number of attributes mapped into the XmlElement
		static int mapTupleToElement(const std::map<std::string,std::string>& tuple, cgi::xml::XmlElement& xelement);
		
		/// Get access to the children 
		const std::vector< cgi::xml::XmlElement >& getChildren() const;
		
	protected:
	
		///
		/// Element name
		///
		std::string _name;
		
		///
		/// Name Space alias
		///
		std::string _ns;
		
		///
		/// Name / value attributes of the elements
		///
		std::map< std::string, std::string> _attribs;
		
		///
		/// Sub Elements of this Element
		///
		std::vector< cgi::xml::XmlElement > _children;
		
		///
		///
		///
		std::string _content;
		
};

}
; // End of cgi::xml namespace

}
; // End of cgi namespace


#endif /* _CGI_XMLELEMENT_H_ */

