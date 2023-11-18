// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//		   The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Raw Pointers.
		for (size_t i = 0; i < allProfiles.size(); ++i)
		{
			//check if banned
			bool profileBanned = false;
			for (size_t j = 0; j < bannedProfiles.size() && !profileBanned; ++j)
			{
				profileBanned = (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name) && (allProfiles[i].m_age == bannedProfiles[j].m_age);
				//profileBanned = (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_age == bannedProfiles[j].m_age);
			}



			if (!profileBanned)
			{
				//validate address
				Profile* prof = new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age);
				try 
				{
					prof->validateAddress();
				}
				catch(...)
				{
					delete prof;
					throw;
				}

				result += prof;

				delete prof;
			}
			//else
			//{
			//	std::cout << "\n" << allProfiles[i].m_name << " banned\n";
			//}
		}

		return result;
	}
	
	DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//		   The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Smart Pointers.
		for (size_t i = 0; i < allProfiles.size(); ++i)
		{
			//check if banned
			bool profileBanned = false;
			for (size_t j = 0; j < bannedProfiles.size() && !profileBanned; ++j)
			{
				profileBanned = (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_name.last_name == bannedProfiles[j].m_name.last_name) && (allProfiles[i].m_age == bannedProfiles[j].m_age);
				//profileBanned = (allProfiles[i].m_name.first_name == bannedProfiles[j].m_name.first_name) && (allProfiles[i].m_age == bannedProfiles[j].m_age);
			}



			if (!profileBanned)
			{
				std::shared_ptr<Profile> p(new Profile(allProfiles[i].m_name, allProfiles[i].m_address, allProfiles[i].m_age));

				//validate address
				p->validateAddress();

				result += p;
			}
		}




		return result;
	}
}
