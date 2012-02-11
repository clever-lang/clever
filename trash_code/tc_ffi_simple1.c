#include <stdio.h>
#include <ffi.h>

int f(int a, int b)
{
	printf("here %d %d\n",a,b);
	return a+b;
}

int main()
{
	ffi_cif cif, cif2;
	ffi_type *args[1], *args2[2];
	void *values[1], *values2[2];
	char *s;
	int rc;

	/* Initialize the argument info vectors */
	args[0] = &ffi_type_pointer;
	values[0] = &s;

	/* Initialize the cif */
	if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1,
				&ffi_type_uint, args) == FFI_OK)
		{
		s = "Hello World!";
		ffi_call(&cif, puts, &rc, values);
		/* rc now holds the result of the call to puts */

		/* values holds a pointer to the function's arg, so to
			call puts() again all we need to do is change the
			value of s */
		s = "This is cool!";
		ffi_call(&cif, puts, &rc, values);
		}
	
	
	args2[0]=&ffi_type_sint32; args2[1]=&ffi_type_sint32;
	
	int in[2];
	
	in[0]=1; in[1]=2;
	values2[0]=&in[0];	values2[1]=&in[1];
	
	if	(ffi_prep_cif(&cif2, FFI_DEFAULT_ABI, 2, &ffi_type_sint32, args2) == FFI_OK)
	{
		ffi_call(&cif2,f,&rc,values2);
		printf("r=%d\n",rc);
	}
	
	return 0;
}