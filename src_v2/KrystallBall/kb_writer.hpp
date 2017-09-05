
#ifndef _kb_writer_
#define _kb_writer_

#include "kb_discrete_model.hpp"
#include <string>
#include <vector>

namespace kb {

	class writer : public discrete::model {
	public:

		template<typename T>
		void addVariable(const std::string & varname, T * var_ref) {}

		virtual void init() {
			b_vars.clear();
			i_vars.clear();
			u_vars.clear();
			f_vars.clear();
			d_vars.clear();

			b_varn.clear();
			i_varn.clear();
			u_varn.clear();
			f_varn.clear();
			d_varn.clear();
		} 

	protected:

		// containers storing references to 
		// variables we wish to write to file
		std::vector<bool*>			b_vars;
		std::vector<int*>			i_vars;
		std::vector<unsigned int*>	u_vars;
		std::vector<float*>			f_vars;
		std::vector<double*>		d_vars;

		// containers storing variable names
		// for variables we wish to write to file
		std::vector<std::string>	b_varn;
		std::vector<std::string>	i_varn;
		std::vector<std::string>	u_varn;
		std::vector<std::string>	f_varn;
		std::vector<std::string>	d_varn;

	};

	
	template<>
	inline void writer::addVariable(const std::string & varname, bool * var_ref)
	{
		b_vars.push_back(var_ref);
		b_varn.push_back(varname);
	}
	
	template<>
	inline void writer::addVariable(const std::string & varname, int * var_ref)
	{
		i_vars.push_back(var_ref);
		i_varn.push_back(varname);
	}
	
	template<>
	inline void writer::addVariable(const std::string & varname, unsigned int * var_ref)
	{
		u_vars.push_back(var_ref);
		u_varn.push_back(varname);
	}
	
	template<>
	inline void writer::addVariable(const std::string & varname, float * var_ref)
	{
		f_vars.push_back(var_ref);
		f_varn.push_back(varname);
	}
	
	template<>
	inline void writer::addVariable(const std::string & varname, double * var_ref)
	{
		d_vars.push_back(var_ref);
		d_varn.push_back(varname);
	}

}


#endif
