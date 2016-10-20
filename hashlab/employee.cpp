#include <string>
// Example of an Employee class
class Employee
{
  public:
		Employee (const std::string & n, double sal, int sen) : 
			name(n), salary(sal), seniority(sen) {}

		~Employee() {
			clear();
		}

    const std::string& getName( ) const
      { return name; }
    bool operator==( const Employee & rhs ) const
      { return getName( ) == rhs.getName( ); }
    bool operator!=( const Employee & rhs ) const
      { return !( *this == rhs );  }

      // Additional public members not shown

  private:
    std::string name;
    double salary;
    int    seniority;
		
		void clear(){
		}
      // Additional private members not shown
};

int hash( const std::string & key );

int hash( const Employee & item ) {
	std::string str = item.getName();
	return hash( str );
}

