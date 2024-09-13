module;

export module cylinder;

const double PI {3.1415926535897932384626433832795};


export class Cylinder {
    public : 
        //Constctors
        Cylinder() = default;
        Cylinder(double rad_param,double height_param){
            base_radius = rad_param;
            height = height_param;
        }
        //Functions (methods)
        double volume(){
            return PI * base_radius * base_radius * height;
        }
        
        //Setter and getter methods
        double get_base_radius(){
            return base_radius;
        }
        double get_height(){
            return height;
        }

        void set_base_radius(double rad_param){
            base_radius = rad_param;
        }

        void set_height(double height_param){
            height = height_param;
        }
    private : 
        //Member variables
        double base_radius{1};
        double height{1};
};