std::string kernel_code =
	" void kernel move_dinosaurs(__global int* states,"
	" 						     __global int* pos_x,"
	" 						     __global int* fitness,"
	" 						     const float speed) {"

	" 	int ID;"
	" 	ID = get_global_id(0);"

	" 	if (states[ID] == 3) {"
	" 		pos_x[ID] = pos_x[ID] + speed;"

	" 	} else {"

	" 		if (states[ID] == 0 || states[ID] == 1) {"
	" 			fitness[ID] = fitness[ID] + 2.0;"
	" 		}"
	" 		else {"
	" 			fitness[ID] = fitness[ID] + 1.0;"
	" 		}"

	" 	}"
	" }";