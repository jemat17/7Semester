#include <opencv2/highgui.hpp>
#include <iostream>

void menu(cv::Mat image)
{
  std::string image1;
  int switchcase;

  std::cout << "Menu: " << std::endl  << "Press 1 to select a picture" << std::endl;
  std::cout << "Press 2 to show image" << std::endl << "Press 3 to increase the brightness by 100" << std::endl;
  std::cout << "Press 4 to decrease the brightness by 100" << std::endl << "Any other key to exit" << std::endl;

  std::cin >> switchcase;

   switch (switchcase)
 {
 case 1:
    
    std::cout << "What is the name of your image?" << std::endl;
    std::cin >> image1;
    image1 += ".jpg";
    image = cv::imread(image1, cv::IMREAD_COLOR);
    system("clear");
    menu(image);
       // Check for failure and try agian
    if (image.empty()) 
      {
      std::cout << "Could not open or find the image" << std::endl;
      std::cout << "press 1 to try agian. Press any other key to exit" << std::endl;
      int option;
      std::cin >> option;
    if(option == 1)
      {
      std::cout << "What is the name of your image?" << std::endl;
      std::cin >> image1; 
      image1 += ".jpg";
      image = cv::imread(image1, cv::IMREAD_COLOR);
      system("clear");
      menu(image);
      }
    else 
      {
      std::cin.get(); //wait for any key press
      break;
      }
    }
   
 
 case 2:
    cv::namedWindow(image1); // Create window 
    cv::imshow(image1, image); // Show window 
    cv::waitKey(0);    // Close window whan key pressed
    cv::destroyWindow(image1); //close window.
    system("clear");
    menu(image);
    
  
  case 3:
    image.convertTo(image, -1, 1, 100); //increase the brightness by 100
    system("clear");
    menu(image);
    

  case 4:
    image.convertTo(image, -1, 1, -100); //decrease the brightness by 100
    system("clear");
    menu(image);
    
 default:
 
   break;
 } 
}
 
int main() {

  // Create image object
  cv::Mat image;

  menu(image);

  return 0;
}