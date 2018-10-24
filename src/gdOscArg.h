#ifndef _GDOSCARG_
#define _GDOSCARG_

#include <string>

namespace gdosc {
	
	typedef enum _gdOscArgType { TYPE_NONE, TYPE_INT32, TYPE_FLOAT, TYPE_STRING } gdOscArgType;

	class gdOscArg {
		
		public:
		
			virtual ~gdOscArg(){};
			virtual gdOscArgType getType() const { return TYPE_NONE; }
			virtual std::string getTypeName() const { return "none"; }
			
	};

	class gdOscArgInt32 : public gdOscArg {
			
		public:
			
			gdOscArgInt32(int32_t _value) { value = _value; }

			/// return the type of this argument
			gdOscArgType getType() const { return TYPE_INT32; }
			std::string getTypeName() const { return "int32"; }

			/// return value
			int32_t get() const { return value; }
			/// set value
			void set(int32_t _value) { value = _value; }

		private:
		
			int32_t value;
		
	};

	class gdOscArgFloat : public gdOscArg {
		
		public:
		
			gdOscArgFloat(float _value) { value = _value; }

			/// return the type of this argument
			gdOscArgType getType() const { return TYPE_FLOAT; }
			std::string getTypeName() const { return "float"; }

			/// return value
			float get() const { return value; }
			/// set value
			void set(float _value) { value = _value; }

		private:
		
			float value;
		
	};

	class gdOscArgString : public gdOscArg {
		
		public:
		
			gdOscArgString(std::string _value) { value = _value; }

			/// return the type of this argument
			gdOscArgType getType() const { return TYPE_STRING; }
			std::string getTypeName() const { return "string"; }

			/// return value
			std::string get() const { return value; }
			/// set value
			void set(const char* _value) { value = _value; }

		private:
				
			std::string value;
			
	};

};

#endif
