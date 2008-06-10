#define TPL_USE_AUTO_ALLOC
#include <vector>		// std::vector
#include <iostream> 	// std::cout
#include <tpl/c/Lex.h>	// c_comment()
#include <tpl/RegExp.h>
/* is */ # /* it */ include /* supported? no problem! */ <stdext/FileBuf.h>

using namespace tpl;

// -------------------------------------------------------------------------
// list include files

int main()
{
	std::vector<impl::Leaf> result;

	simple::Allocator alloc;

	simple::Rule rInclude( alloc,
		simple::skipper( skipws() % c_comment() /* ("/*" + find<true>("*\/")) */ ) >>
		(gr('#') + "include" + '<' + find('>')/assign(result) + '>') );

	simple::Rule rDoc( alloc, *(!rInclude + find_strict_eol<true>()) );

	const std::FileBuf file(__FILE__);
	if ( simple::match(file.begin(), file.end(), rDoc) ) {
		for (std::vector<impl::Leaf>::iterator it = result.begin(); it != result.end(); ++it)
			std::cout << *it << '\n';
	}
	return 0;
}

// -------------------------------------------------------------------------
