#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Struct to represent a task with title, completion status, and priority.
struct Task {
	string title; //Title or description of the task.
	bool completed; //Indicates whether the task is completed(true) or not(false).
	int priority; //Priority of the task(1 for low, 2 for medium, 3 for high).
};

//Function to add a new task to the task manager application.
void addTask(vector<Task>& tasks) {
	//Declare a new Task object to represent the task to be added.
	Task newTask;

	//Prompt the user to enter the title or description of the task.
	cout << "Enter task title: ";
	//Read the input from the user and store it in the title member variable of the newTask object.
	getline(cin, newTask.title);

	//Prompt the user to enter the priority of the task.
	cout << "Enter task priority (1 - Low, 2 - Medium, 3 - High): ";
	//Read the input from the user and store it in the priority member variable of the newTask object.
	cin >> newTask.priority;
	cin.ignore(); //Clear input buffer.

	//Initialize the completion status of the task to false, indicating it is not yet completed.
	newTask.completed = false;

	//Add the newTask object to the end of the tasks vector, effectively adding the task to the task list.
	tasks.push_back(newTask);

	//Print a message to confirm that the task has been successfully added.
	cout << "Task added successfully!" << endl;
}

//Function to display the list of tasks.
void listTasks(const vector<Task>& tasks) {
	//Check if the tasks vector is empty.
	if (tasks.empty()) {
		//If the vector is empty, print a message indicating no tasks are found.
		cout << "No tasks found." << endl;
		//Return from the function as there are no tasks to display.
		return;
	}

	//If there are tasks in the vector, print the header for the task list.
	cout << "Task List: " << endl;

	//Iterate over each task in the tasks vetor using a for loop.
	for (size_t i= 0; i < tasks.size(); i++) {
		//Retrieve the current task from the vector.
		const Task& task = tasks[i];

		//Print the task number, title, priority, and completion status.
		//Task number is i + 1 because indexing starts from 0 but task numbers start from 1.
		cout << i + 1 << ". " << task.title << " = Priority: ";

		//Switch statement to determine the priority of the task.
		switch (task.priority) {
			case 1:
				cout << "Low";
				break;
			case 2:
				cout << "Medium";
				break;
			case 3:
				cout << "High";
				break;
			default:
				cout << "Unknown";
		
		}
		//Print the completion status of the task.
		//If task.completed is true, print "Completed", otherwise print "Incomplete".
		cout << " - " << (task.completed ? "Completed" : "Incomplete") << endl;

	}
}

//Function to mark a task as completed.
void markTaskCompleted(vector<Task>& tasks) {
	//Display the current list of tasks to the user.
	listTasks(tasks);

	//Prompt the user to enter the index of the task to mark as completed.
	cout << "Enter the index of the task to mark as completed: ";
	int index;
	//Read the user's input index from the console.
	cin >> index;

	//Validate the input index.
	if (index > 0 && index <= tasks.size()) {
		//If the input index is valid (within the range of tasks vector), mark the selected task as completed.
		tasks[index - 1].completed = true;
		//Print a message to confirm that the task has been marked as completed.
		cout << "Task marked as completed!" << endl;
	}
	else {
		//If the input index is invalid, print an error message.
		cout << "Invalid task index!" << endl;
	}
}
//Function to save tasks to a file.
void saveTasks(const vector<Task>& tasks, const string& filename) {
	//Open the file for writing.
	ofstream file(filename);

	//Check if the file was successfully opened.
	if (file.is_open()) {
		//If the file is open, iterate through each task in the tasks vector.
		for (const Task& task : tasks) {
			//Write the task details (title, completed status, and priority) to the file.
			file << task.title << "," << task.completed << "," << task.priority << endl;

		}
		//Close the file after writing.
		file.close();

		//Print a message to confirm that tasks have been successfully saved to the file.
		cout << "Tasks saved to file: " << filename << endl;
	}
	else {
		//If the file cannot be opened for writing, print an error message.
		cerr << "Unable to open file for writing: " << filename << endl;
	}

}
//Function to load tasks.
void loadTasks(vector<Task>& tasks, const string& filename) {
	tasks.clear(); //Clear existing tasks.
	ifstream file(filename); //Creates an input file stream 'file' and opens the file specified by the 'filename' string.
	//Check if the file was successfully opened.
	if (file.is_open()) {
		string line;
		//Reads each line from the file.
		while (getline(file, line)) {
			//Creates a new 'Task' object 'task' to hold the information of the current task.
			Task task;
			//Find the position of the first comma to separate the title.
			size_t pos = line.find(",");
			//Extracts the title from the beginning of the line until the position of the comma.
			task.title = line.substr(0, pos);
			//Removes the extracted title and the comma from the line.
			line.erase(0, pos + 1); 
			//Converts the first character of the remaining line to an integer and assigns it to 'task.completed'.
			task.completed = line[0] - '0';
			//Removes the comma and space following the completion status from the line.
			line.erase(0, 2);
			//Converts the remaining line(representing the priority) to an integer and assigns it to 'task.priority'.
			task.priority = stoi(line);
			//Add the loaded task to the vector.
			tasks.push_back(task);
		}
		//Close the file after reading.
		file.close();
		cout << "Tasks loaded from file: " << filename << endl;
	}
	else {
		//If the file cannot be opened, display an error message.
		cerr << "Unable to open file for reading: " << filename << endl;
	}
}
int main() {
	vector<Task> tasks; //Create a vector to store Task objects.
	const string filename = "tasks.txt"; //Specify the filename for data persistence.

	//Load tasks from file at the start.
	loadTasks(tasks, filename);

	int choice;
	while (true) {
		//Display the menu options to the user.
		cout << "\nTask Manager Menu: " << endl;
		cout << "1. Add Task" << endl;
		cout << "2. Lists Tasks" << endl;
		cout << "3. Mark Task as Completed" << endl;
		cout << "4. Save Tasks" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice; //Read the user's choice.
		cin.ignore(); //Clear the input buffer.

		switch (choice) {
			case 1:
				addTask(tasks); //Call the function to add a new task.
				break;
			case 2:
				listTasks(tasks); //Call the function to list all tasks.
				break;
			case 3:
				markTaskCompleted(tasks); //Call the function to mark a task as completed.
				break;
			case 4:
				saveTasks(tasks, filename); //Call the function to save tasks to a file.
				break;
			case 5:
				//Save tasks to file before exiting.
				saveTasks(tasks, filename);
				cout << "Exiting program. Goodbye!" << endl; //Display exit message.
				return 0; //Return from main function to exit the program.
			default:
				cout << "Invalid choice. Please try again." << endl; //Display error message for invalid input.

		}
	}
	return 0; //Ensure that the function returns an integer.
}