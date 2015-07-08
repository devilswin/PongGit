#ifndef BOOK_CATEGORY_HPP
#define BOOK_CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		Scene				= 1 << 0,
		Plyr				= 1 << 1,
		Comp				= 1 << 2,
		Ball				= 1 << 3,
		
	};
}

#endif // BOOK_CATEGORY_HPP
