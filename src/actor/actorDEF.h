#define PROPERTIES_ARRAY(prop)																			\
	std::list<void *> Array_##prop;	


#define INSERT_PROPERTY(prop)																			\
	if (Property::prop * x = dynamic_cast<Property::prop *>(component))								\
	{																									\
		Array_##prop.push_front( reinterpret_cast<void *>(x));											\
		aggregation.second.push_back(Array_##prop.begin());												\
	}

#define REMOVE_PROPERTY(prop)																			\
	Array_##prop.remove(*property);

#define MOVE_PROPERTY(prop)																				\
	Array_##prop = std::move(otherActor.Array_##prop)

// TODO review Process 
#define PROCESS_PROPERTY(prop, WhatToDo, param1, param2)												\
	for (auto && x : Array_##prop)																		\
	{																									\
		reinterpret_cast<Property::prop *>(x)->WhatToDo(param1);										\
	}
