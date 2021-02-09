#define PROPERTIES_ARRAY(prop)																			\
	std::list<void *> Array_##prop;	


#define INSERT_PROPERTY(prop)																			\
	if (Property::##prop * x = dynamic_cast<Property::##prop *>(component))								\
	{																									\
		Array_##prop.push_front( reinterpret_cast<void *>(x));											\
		aggregation.second.push_back(Array_##prop.begin());												\
	}

#define REMOVE_PROPERTY(prop)																			\
	Array_##prop.remove(*property);
