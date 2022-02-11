#ifndef PARAMS_HPP
#define PARAMS_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <thread>
#include <mutex>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <typeinfo>
#include <map>
#include <boost/lexical_cast.hpp>
namespace pf
{   
    class Params
    {
    private:
		std::map<std::string, int> db_int;
		std::map<std::string, bool> db_bool;
		std::map<std::string, std::string> db_str;
		std::map<std::string, double> db_double;

    public:
		std::string module_name;

        Params(const std::string &_module_name) :
			module_name(_module_name)
        {
        }
        Params(){}
		inline void add_params(const std::string &_key, const int &_value)
		{
			std::pair<std::string, int> tmp_data;
			tmp_data.first = _key;
			tmp_data.second = _value;
			this->db_int.insert(tmp_data);
		}
		inline void add_params(const std::string &_key, const bool &_value)
		{
			std::pair<std::string, bool> tmp_data;
			tmp_data.first = _key;
			tmp_data.second = _value;
			this->db_bool.insert(tmp_data);
		}
		inline void add_params(const std::string &_key, const std::string &_value)
		{
			std::pair<std::string, std::string> tmp_data;
			tmp_data.first = _key;
			tmp_data.second = _value;
			this->db_str.insert(tmp_data);
		}
		inline void add_params(const std::string &_key, const double &_value)
		{
			std::pair<std::string, double> tmp_data;
			tmp_data.first = _key;
			tmp_data.second = _value;
			this->db_double.insert(tmp_data);
		}
		void print_params()
		{
			for(auto iter = this->db_int.begin(); iter != this->db_int.end(); iter++)
				ROS_WARN("%s%s %d", this->module_name.c_str(), iter->first.c_str(), iter->second);
			for(auto iter = this->db_bool.begin(); iter != this->db_bool.end(); iter++)
				ROS_WARN("%s%s %d", this->module_name.c_str(), iter->first.c_str(), iter->second);
			for(auto iter = this->db_str.begin(); iter != this->db_str.end(); iter++)
				ROS_WARN("%s%s %s", this->module_name.c_str(), iter->first.c_str(), iter->second.c_str());
			for(auto iter = this->db_double.begin(); iter != this->db_double.end(); iter++)
				ROS_WARN("%s%s %lf", this->module_name.c_str(), iter->first.c_str(), iter->second);
		}
		inline int get_int(const std::string &_param)
		{
			if(db_int.find(_param) != db_int.end())
			{
				int value = db_int.find(_param)->second;
				return value;
			}
			else
			{
				ROS_ERROR("not found [%s] value..", _param.c_str());
			}
		}
		inline bool get_bool(const std::string &_param)
		{
			if(db_bool.find(_param) != db_bool.end())
			{
				bool value = db_bool.find(_param)->second;
				return value;
			}
			else
			{
				ROS_ERROR("not found [%s] value..", _param.c_str());
			}
		}
		inline std::string get_str(const std::string &_param)
		{
			if(db_str.find(_param) != db_str.end())
			{
				std::string value = db_str.find(_param)->second;
				return value;
			}
			else
			{
				ROS_ERROR("not found [%s] value..", _param.c_str());
			}
		}
		inline double get_double(const std::string &_param)
		{
			if(db_double.find(_param) != db_double.end())
			{
				double value = db_double.find(_param)->second;
				return value;
			}
			else
			{
				ROS_ERROR("not found [%s] value..", _param.c_str());
			}
		}
		inline void set(const std::string &_param, const int _value)
		{
			if(db_int.find(_param) == db_int.end())
			{
				ROS_ERROR("Cannot edit [%s] param..", _param.c_str());
				return;
			}
			db_int[_param] = _value;
		}
        inline void set(const std::string &_param, const bool _value)
		{
			if(db_bool.find(_param) == db_bool.end())
			{
				ROS_ERROR("Cannot edit [%s] param..", _param.c_str());
				return;
			}
			db_bool[_param] = _value;
		}
		inline void set(const std::string &_param, const std::string _value)
		{
			if(db_str.find(_param) == db_str.end())
			{
				ROS_ERROR("Cannot edit [%s] param..", _param.c_str());
				return;
			}
			db_str[_param] = _value;

		}
		inline void set(const std::string &_param, const double _value)
		{
			if(db_double.find(_param) == db_double.end())
			{
				ROS_ERROR("Cannot edit [%s] param..", _param.c_str());
				return;
			}
			db_double[_param] = _value;
		}
        void read_params(ros::NodeHandle &_n_param)
        {
			bool valid_int = true;
			bool valid_bool = true;
			bool valid_str = true;
			bool valid_double = true;
			for(auto iter = this->db_int.begin(); iter != this->db_int.end(); iter++)
            {
                int value;
                valid_int = _n_param.getParam(cv::format("%s%s", this->module_name.c_str(), iter->first.c_str()), value);
                this->set(iter->first, value);
				if(!valid_int)	break;	
            }
			for(auto iter = this->db_bool.begin(); iter != this->db_bool.end(); iter++)
            {
                bool value;
                valid_bool = _n_param.getParam(cv::format("%s%s", this->module_name.c_str(), iter->first.c_str()), value);
                this->set(iter->first, value);
				if(!valid_bool)	break;	
            }
			for(auto iter = this->db_str.begin(); iter != this->db_str.end(); iter++)
            {
                std::string value;
                valid_str = _n_param.getParam(cv::format("%s%s", this->module_name.c_str(), iter->first.c_str()), value);
                this->set(iter->first, value);
				if(!valid_str)	break;	
            }
			for(auto iter = this->db_double.begin(); iter != this->db_double.end(); iter++)
            {
                double value;
                valid_double = _n_param.getParam(cv::format("%s%s", this->module_name.c_str(), iter->first.c_str()), value);
                this->set(iter->first, value);
				if(!valid_double)	break;	
            }
			if(!valid_int || !valid_bool || !valid_str || !valid_double)	
				ROS_ERROR("[%s]Fail to read parameters in launch file..", this->module_name.c_str());
			else
				ROS_WARN("[%s]Success to read parameters in launch file!", this->module_name.c_str());
        }
		void param2json(Json::Value &_root)
		{
			for(auto iter = this->db_int.begin(); iter != this->db_int.end(); iter++)
            {
				_root[this->module_name + iter->first] = iter->second;
            }
			for(auto iter = this->db_bool.begin(); iter != this->db_bool.end(); iter++)
            {
				_root[this->module_name + iter->first] = iter->second;
            }
			for(auto iter = this->db_str.begin(); iter != this->db_str.end(); iter++)
            {
				_root[this->module_name + iter->first] = iter->second;
            }
			for(auto iter = this->db_double.begin(); iter != this->db_double.end(); iter++)
            {
				_root[this->module_name + iter->first] = iter->second;
            }
		}
        bool checkParams(const std::string &_str)
		{
			if((int)_str.length() <= 0)		return false;

			std::string input_module_name;
			std::string key;
			std::string value;
			std::vector<std::string> spliter_module;
			std::vector<std::string> spliter_key;
			std::stringstream ss_module(_str);
			std::string temp_str;
			while(getline(ss_module, temp_str, '/'))
			{
				spliter_module.push_back(temp_str);
			}
			if((int)spliter_module.size() < 4)			return false;
			input_module_name = spliter_module[2];		// color
			input_module_name = "/tracker/" + input_module_name;
			if(this->module_name != input_module_name)	return false;

			std::string _str_key = spliter_module[3];
			std::stringstream ss_key(_str_key);
			while(getline(ss_key, temp_str, ','))
			{
				spliter_key.push_back(temp_str);
			}
			if((int)spliter_key.size() != 2)			return false;
			key = "/" + spliter_key[0];		// "/plot"
			value = spliter_key[1];			// "true"

			bool valid_output;
			if(db_int.find(key) != db_int.end())	//stoi
			{
				int tmp_value = std::stoi(value);
				this->set(key, tmp_value);		//edit new value
				ROS_WARN("Edit! ->[%s] key: %s, value: %s", input_module_name.c_str(), key.c_str(), value.c_str());
				valid_output = true;
			}
			else if(db_bool.find(key) != db_bool.end())
			{
				//bool tmp_value = boost::lexical_cast<bool>(value);
				bool tmp_value = (value == "true");
				this->set(key, tmp_value);		//edit new value
				ROS_WARN("Edit! ->[%s] key: %s, value: %s", input_module_name.c_str(), key.c_str(), value.c_str());
				valid_output = true;
			}
			else if(db_str.find(key) != db_str.end())
			{
				this->set(key, value);		//edit new value
				ROS_WARN("Edit! ->[%s] key: %s, value: %s", input_module_name.c_str(), key.c_str(), value.c_str());
				valid_output = true;
			}
			else if(db_double.find(key) != db_double.end())
			{
				double tmp_value = std::stod(value);
				this->set(key, tmp_value);		//edit new value
				ROS_WARN("Edit! ->[%s] key: %s, value: %s", input_module_name.c_str(), key.c_str(), value.c_str());
				valid_output = true;
			}
			else
				valid_output = false;

			return valid_output;
		}
    };
}

#endif