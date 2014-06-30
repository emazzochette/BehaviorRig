#pragma once


namespace BehaviorRig {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace msclr::interop;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class BehaviorRigMainForm : public System::Windows::Forms::Form
	{
	public:
		BehaviorRigMainForm(void)
		{
			zaber = gcnew Zaber;
			experiment = new Experiment;
			//timing = new Timing;
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~BehaviorRigMainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  startTrackButton;
	private: System::Windows::Forms::Button^  stopTrackButton;
	private: System::Windows::Forms::Button^  setUpExperimentButton;
	protected: 

	protected: 


	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::Label^  trackerStatusLabel;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	private: Experiment *experiment;
	private: System::Windows::Forms::GroupBox^  inputModeGroupBox;
	private: System::Windows::Forms::RadioButton^  videoModeRadioButton;
	private: System::Windows::Forms::RadioButton^  cameraModeRadioButton;
	private: System::Windows::Forms::OpenFileDialog^  openVideoFileDialog;
	private: System::Windows::Forms::TextBox^  videoFileTextBox;

	private: System::Windows::Forms::Button^  videoFileBrowseButton;
	private: System::Windows::Forms::Label^  videoFileNameLabel;
	private: System::Windows::Forms::RadioButton^  imageModeRadioButton;

			 //private: Timing *timing;
	private: Zaber^ zaber;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->startTrackButton = (gcnew System::Windows::Forms::Button());
			this->stopTrackButton = (gcnew System::Windows::Forms::Button());
			this->setUpExperimentButton = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->trackerStatusLabel = (gcnew System::Windows::Forms::Label());
			this->inputModeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->imageModeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->videoModeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->cameraModeRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->openVideoFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->videoFileTextBox = (gcnew System::Windows::Forms::TextBox());
			this->videoFileBrowseButton = (gcnew System::Windows::Forms::Button());
			this->videoFileNameLabel = (gcnew System::Windows::Forms::Label());
			this->inputModeGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// startTrackButton
			// 
			this->startTrackButton->Location = System::Drawing::Point(13, 230);
			this->startTrackButton->Name = L"startTrackButton";
			this->startTrackButton->Size = System::Drawing::Size(75, 23);
			this->startTrackButton->TabIndex = 0;
			this->startTrackButton->Text = L"Start Track";
			this->startTrackButton->UseVisualStyleBackColor = true;
			this->startTrackButton->Click += gcnew System::EventHandler(this, &BehaviorRigMainForm::startTrackButton_Click);
			// 
			// stopTrackButton
			// 
			this->stopTrackButton->Location = System::Drawing::Point(12, 259);
			this->stopTrackButton->Name = L"stopTrackButton";
			this->stopTrackButton->Size = System::Drawing::Size(75, 23);
			this->stopTrackButton->TabIndex = 1;
			this->stopTrackButton->Text = L"Stop Track";
			this->stopTrackButton->UseVisualStyleBackColor = true;
			this->stopTrackButton->Click += gcnew System::EventHandler(this, &BehaviorRigMainForm::stopTrackButton_Click);
			// 
			// setUpExperimentButton
			// 
			this->setUpExperimentButton->Location = System::Drawing::Point(12, 12);
			this->setUpExperimentButton->Name = L"setUpExperimentButton";
			this->setUpExperimentButton->Size = System::Drawing::Size(117, 23);
			this->setUpExperimentButton->TabIndex = 2;
			this->setUpExperimentButton->Text = L"Set Up Experiment";
			this->setUpExperimentButton->UseVisualStyleBackColor = true;
			this->setUpExperimentButton->Click += gcnew System::EventHandler(this, &BehaviorRigMainForm::setUpExperimentButton_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &BehaviorRigMainForm::backgroundWorker1_DoWork);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &BehaviorRigMainForm::backgroundWorker1_ProgressChanged);
			this->backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &BehaviorRigMainForm::backgroundWorker1_RunWorkerCompleted);
			// 
			// trackerStatusLabel
			// 
			this->trackerStatusLabel->AutoSize = true;
			this->trackerStatusLabel->Location = System::Drawing::Point(103, 259);
			this->trackerStatusLabel->Name = L"trackerStatusLabel";
			this->trackerStatusLabel->Size = System::Drawing::Size(35, 13);
			this->trackerStatusLabel->TabIndex = 3;
			this->trackerStatusLabel->Text = L"label1";
			// 
			// inputModeGroupBox
			// 
			this->inputModeGroupBox->Controls->Add(this->imageModeRadioButton);
			this->inputModeGroupBox->Controls->Add(this->videoModeRadioButton);
			this->inputModeGroupBox->Controls->Add(this->cameraModeRadioButton);
			this->inputModeGroupBox->Location = System::Drawing::Point(13, 51);
			this->inputModeGroupBox->Name = L"inputModeGroupBox";
			this->inputModeGroupBox->Size = System::Drawing::Size(103, 92);
			this->inputModeGroupBox->TabIndex = 4;
			this->inputModeGroupBox->TabStop = false;
			this->inputModeGroupBox->Text = L"Input Mode";
			// 
			// imageModeRadioButton
			// 
			this->imageModeRadioButton->AutoSize = true;
			this->imageModeRadioButton->Location = System::Drawing::Point(7, 66);
			this->imageModeRadioButton->Name = L"imageModeRadioButton";
			this->imageModeRadioButton->Size = System::Drawing::Size(86, 17);
			this->imageModeRadioButton->TabIndex = 2;
			this->imageModeRadioButton->TabStop = true;
			this->imageModeRadioButton->Text = L"Single Image";
			this->imageModeRadioButton->UseVisualStyleBackColor = true;
			// 
			// videoModeRadioButton
			// 
			this->videoModeRadioButton->AutoSize = true;
			this->videoModeRadioButton->Location = System::Drawing::Point(7, 42);
			this->videoModeRadioButton->Name = L"videoModeRadioButton";
			this->videoModeRadioButton->Size = System::Drawing::Size(52, 17);
			this->videoModeRadioButton->TabIndex = 1;
			this->videoModeRadioButton->Text = L"Video";
			this->videoModeRadioButton->UseVisualStyleBackColor = true;
			// 
			// cameraModeRadioButton
			// 
			this->cameraModeRadioButton->AutoSize = true;
			this->cameraModeRadioButton->Checked = true;
			this->cameraModeRadioButton->Location = System::Drawing::Point(7, 19);
			this->cameraModeRadioButton->Name = L"cameraModeRadioButton";
			this->cameraModeRadioButton->Size = System::Drawing::Size(61, 17);
			this->cameraModeRadioButton->TabIndex = 0;
			this->cameraModeRadioButton->TabStop = true;
			this->cameraModeRadioButton->Text = L"Camera";
			this->cameraModeRadioButton->UseVisualStyleBackColor = true;
			// 
			// openVideoFileDialog
			// 
			this->openVideoFileDialog->FileName = L"openVideoFileDialog";
			// 
			// videoFileTextBox
			// 
			this->videoFileTextBox->Location = System::Drawing::Point(13, 162);
			this->videoFileTextBox->Name = L"videoFileTextBox";
			this->videoFileTextBox->Size = System::Drawing::Size(160, 20);
			this->videoFileTextBox->TabIndex = 5;
			// 
			// videoFileBrowseButton
			// 
			this->videoFileBrowseButton->Location = System::Drawing::Point(13, 188);
			this->videoFileBrowseButton->Name = L"videoFileBrowseButton";
			this->videoFileBrowseButton->Size = System::Drawing::Size(75, 23);
			this->videoFileBrowseButton->TabIndex = 6;
			this->videoFileBrowseButton->Text = L"Browse";
			this->videoFileBrowseButton->UseVisualStyleBackColor = true;
			this->videoFileBrowseButton->Click += gcnew System::EventHandler(this, &BehaviorRigMainForm::videoFileBrowseButton_Click);
			// 
			// videoFileNameLabel
			// 
			this->videoFileNameLabel->AutoSize = true;
			this->videoFileNameLabel->Location = System::Drawing::Point(12, 146);
			this->videoFileNameLabel->Name = L"videoFileNameLabel";
			this->videoFileNameLabel->Size = System::Drawing::Size(87, 13);
			this->videoFileNameLabel->TabIndex = 7;
			this->videoFileNameLabel->Text = L"Video File Name:";
			// 
			// BehaviorRigMainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(193, 300);
			this->Controls->Add(this->videoFileNameLabel);
			this->Controls->Add(this->videoFileBrowseButton);
			this->Controls->Add(this->videoFileTextBox);
			this->Controls->Add(this->inputModeGroupBox);
			this->Controls->Add(this->trackerStatusLabel);
			this->Controls->Add(this->setUpExperimentButton);
			this->Controls->Add(this->stopTrackButton);
			this->Controls->Add(this->startTrackButton);
			this->Name = L"BehaviorRigMainForm";
			this->Text = L"BehaviorRig";
			this->inputModeGroupBox->ResumeLayout(false);
			this->inputModeGroupBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void startTrackButton_Click(System::Object^  sender, System::EventArgs^  e) {
				//Disable the start track button
				 this->startTrackButton->Enabled = false;

				 //Enable the stop track button
				 this->stopTrackButton->Enabled = true;

				 //set input mode;
				 if( cameraModeRadioButton->Checked == true && videoModeRadioButton->Checked == false)
					 experiment->exp.inputMode = "camera";
				 else if ( cameraModeRadioButton->Checked == false && videoModeRadioButton->Checked == true){
					 if(experiment->exp.videoFilename.empty()){
						 MessageBox::Show("Please enter a video filename");
						 return;
					 }
					 else{
						experiment->exp.inputMode = "video";
						experiment->OpenVideo(experiment->exp.videoFilename);
					 }
				 }
				 else if(imageModeRadioButton->Checked == true){
					 if(experiment->exp.videoFilename.empty()){
						 MessageBox::Show("Please enter an image filename");
						 return;
					 }
					 else{
						experiment->exp.inputMode = "image";
						//experiment->OpenVideo(experiment->exp.videoFilename);
					 }
				 }
				 else
					 return;

				 //Start the asynchronous operation
				 backgroundWorker1->RunWorkerAsync(30);
			 }
	private: System::Void stopTrackButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 //Cancel the asynchronous operation
				 this->backgroundWorker1->CancelAsync();

				 //Disable the stop button
				 stopTrackButton->Enabled = false;

				 ////Enable the start button
				 //startTrackButton->Enabled = true;
			 }
private: System::Void backgroundWorker1_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
			  //Get the BackgroundWorker that raised this event.
				 BackgroundWorker^ worker = dynamic_cast<BackgroundWorker^>(sender);

				  //Assign the result of the computation
				 //to the Result property of the DoWorkEventErgs
				 //object. This will be available to the 
				 //RunWorkerCompleted eventhandler.
				 //e->Result = experiment->trackWorm(safe_cast<Int32>(e->Argument), worker, e);
				 e->Result = trackWorm(safe_cast<Int32>(e->Argument), worker, e);
		 }
private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) {

			

			 array<double>^ testArr = safe_cast<array<double>^>(e->UserState);
			 trackerStatusLabel->Text = System::Convert::ToString( testArr[1]); 

			 //Deal with data:
			 experiment->WriteCurrentFrameData(testArr, zaber->posX, zaber->posY);
			
			 //Start writing video frames to buffer if number of processed frames is more than 4
			 if (testArr[1]>4){
				 experiment->exp.videoWriter << experiment->exp.dataManagement.videoBuffer.back();
				 experiment->exp.dataManagement.videoBuffer.pop_back();
			 }

		

			 experiment->exp.imageControl.grabber.getOverlay()->fill(experiment->exp.imageControl.grabber.getOverlay()->getDropOutColor());
			 RECT rectangle;
			 rectangle.left = (int)experiment->exp.wormAnalysis.PreviousWormData.Target.x/experiment->exp.imageScale-5;
			 rectangle.right = (int)experiment->exp.wormAnalysis.PreviousWormData.Target.x/experiment->exp.imageScale+5;
			 rectangle.top = (int)experiment->exp.wormAnalysis.PreviousWormData.Target.y/experiment->exp.imageScale-5;
			 rectangle.bottom = (int)experiment->exp.wormAnalysis.PreviousWormData.Target.y/experiment->exp.imageScale+5; 
			 experiment->exp.imageControl.grabber.getOverlay()->drawFrameEllipse( RGB(255,0,0), rectangle);
				
			
			

				
		 }
private: System::Void backgroundWorker1_RunWorkerCompleted(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
			  //First, handle the case where an exception is thrown
			 if ( e->Error != nullptr )
			 {
				 MessageBox::Show(e->Error->Message);
			 }
			  else if (e->Cancelled)
			 {
				 //Next, handle the case where the user cancelled
				 //the operation.
				 //Note that due to a race condition in
				 //the DoWork event handler, the Cancelled
				 //flag may not have been set, even though
				 //CancelAsync was called.
				 //resultLabel->Text = "Cancelled";
				 MessageBox::Show("Cancelled");
			 }
			 else
			 {
				 //Finally, handle the case where the operation succeeded.
				 trackerStatusLabel->Text = e->Result->ToString();
			 }

			  //finish writing frames to video:
			  for (std::vector<Mat>::iterator it = experiment->exp.dataManagement.videoBuffer.begin(); it < experiment->exp.dataManagement.videoBuffer.end(); it++ ){
				experiment->exp.videoWriter << *it;
				//experiment->exp.dataManagement.videoBuffer.pop_back();
			  }
			  experiment->EndExperiment();
			  //Enable the start button
			  startTrackButton->Enabled = true;

			  //Disable the stop button
			  stopTrackButton->Enabled = false;
		 }
private: System::Void setUpExperimentButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(zaber->openPort()!=0){
				 MessageBox::Show("The port could not be opened successfully") ;
				return;
			}
			else{
				zaber->SetMoveUnit("Micrometer");
				experiment->exp.imageScale = 0.75;
				experiment->exp.wormAnalysis.imageResizeScale = experiment->exp.imageScale;

				experiment->SetUpCamera();
				experiment->DefineExpProperties();
				experiment->SetUpDataOutput();
			}
		 }

private: int trackWorm(int n, BackgroundWorker^ worker, DoWorkEventArgs ^ e){
			  //Abort the operation if the user has cancelled.
	 //Note that a call to CancelAsync may have set
	 //CancellationPending to true just after the 
	 //last invocation of this method exits, so this
	 //code will not have the oppotunity to set the 
	 //DoWorkEventArgs.Cancel flag to true. This means
	 //the RunWorkerCompletedEventArgs.Cancelled will
	 //not be set to true in your RunWorkerCompleted
	 //event handler. This is a race condition.
	Experiment::doublePoint LocalMoveStage;
	array<double>^ dataArray = gcnew array<double>{1,2,3,4,5,6,7,8,9,10,11,12,13};
	

	TICTOC::timer().tic("WholeWormTrackLoop");
	for (int i=1; i<n+1; i++)
	{
		TICTOC::timer().tic("SingleWormTrackLoop");
		if (worker->CancellationPending )
		{
			e->Cancel = true;
		}
		else
		{
			
			if (experiment->exp.inputMode == "camera"){
				TICTOC::timer().tic("ImageAcqusition");
				experiment->exp.imageControl.GetImage();
				experiment->exp.wormAnalysis.WormImages.OriginalImage = experiment->exp.imageControl.img;
				TICTOC::timer().toc("ImageAcqusition");
			}
			else if (experiment->exp.inputMode == "video"){
				//TICTOC::timer().tic("VideoFrameAcquisition");
				experiment->getNextVideoFrame();
				experiment->exp.wormAnalysis.WormImages.OriginalImage = experiment->exp.currentVideoFrame;
				//TICTOC::timer().toc("VideoFrameAcquisition");
			}
			else if (experiment->exp.inputMode == "image"){
				//TICTOC::timer().tic("ImageFromDiskAcquisition");
				experiment->getImage(experiment->exp.videoFilename);
				experiment->exp.wormAnalysis.WormImages.OriginalImage = experiment->exp.currentVideoFrame;
				//TICTOC::timer().toc("ImageFromDiskAcquisition");
				
			}
			else {
				return -1;
			}
			
			
			
			TICTOC::timer().tic("FindWorm");
			experiment->exp.wormAnalysis.FindWorm();
			TICTOC::timer().toc("FindWorm");
		
			TICTOC::timer().tic("DrawingResultForVideo");
			experiment->exp.wormAnalysis.DrawResult();
			TICTOC::timer().toc("DrawingResultForVideo");
			
			//experiment->exp.wormAnalysis.ShowImage(experiment->exp.wormAnalysis.WormData.ImageToPrint);
			
			
			TICTOC::timer().tic("WriteFrameToVideo");
			experiment->exp.dataManagement.videoBuffer.insert(experiment->exp.dataManagement.videoBuffer.begin(), experiment->exp.wormAnalysis.WormData.ImageToPrint);
			//experiment->exp.videoWriter << experiment->exp.wormAnalysis.WormData.ImageToPrint;
			TICTOC::timer().toc("WriteFrameToVideo");

			experiment->exp.wormAnalysis.WormData.Target.x = experiment->exp.wormAnalysis.WormData.Head.x ;
			experiment->exp.wormAnalysis.WormData.Target.y = experiment->exp.wormAnalysis.WormData.Head.y;
			
			//TICTOC::timer().tic("CalculateStageMovement");
			LocalMoveStage = experiment->DetermineStageMovement(experiment->exp.wormAnalysis.WormData.Target.x, experiment->exp.wormAnalysis.WormData.Target.y);
			//TICTOC::timer().toc("CalculateStageMovement");
			//zaber->getStagePosition();
			TICTOC::timer().tic("StageMovementCommand");
			zaber->moveStageRelative(LocalMoveStage.x,  LocalMoveStage.y);
			TICTOC::timer().toc("StageMovementCommand");
		
			
			
			
		

			//TICTOC::timer().tic("CreateReportProgressDataArray");
			dataArray[0] = 0; //Time Stamp
			dataArray[1] = i; //Processed Frame Count
			dataArray[2] = experiment->exp.imageControl.frameCount; //Frame Number
			dataArray[3] = (double)experiment->exp.wormAnalysis.WormData.Target.x; //Target Position X
			dataArray[4] = (double)experiment->exp.wormAnalysis.WormData.Target.y;
			dataArray[5] = (double)experiment->exp.wormAnalysis.WormData.Head.x;
			dataArray[6] = (double)experiment->exp.wormAnalysis.WormData.Head.y;
			dataArray[7] = (double)experiment->exp.wormAnalysis.WormData.Tail.x;
			dataArray[8] = (double)experiment->exp.wormAnalysis.WormData.Tail.y;
			dataArray[9] = LocalMoveStage.x;
			dataArray[10] = LocalMoveStage.y;
			dataArray[11] = zaber->posX;
			dataArray[12] = zaber->posY;
			//TICTOC::timer().toc("CreateReportProgressDataArray");

			worker->ReportProgress( 0 , dataArray->Clone());
			//Thread::Sleep(1000);
		}
		TICTOC::timer().toc("SingleWormTrackLoop");
		
	}
	TICTOC::timer().toc("WholeWormTrackLoop");
	return 0;
	}
private: System::Void videoFileBrowseButton_Click(System::Object^  sender, System::EventArgs^  e) {
			  msclr::interop::marshal_context context1;

			 if (openVideoFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				videoFileTextBox->Text = openVideoFileDialog->FileName;
				if (openVideoFileDialog->FileName->Length>0)
				{
					experiment->exp.videoFilename = context1.marshal_as<std::string>(openVideoFileDialog->FileName);
				}
			 }
		 }
};
}

