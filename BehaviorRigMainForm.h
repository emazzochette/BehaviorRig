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
			this->SuspendLayout();
			// 
			// startTrackButton
			// 
			this->startTrackButton->Location = System::Drawing::Point(13, 98);
			this->startTrackButton->Name = L"startTrackButton";
			this->startTrackButton->Size = System::Drawing::Size(75, 23);
			this->startTrackButton->TabIndex = 0;
			this->startTrackButton->Text = L"Start Track";
			this->startTrackButton->UseVisualStyleBackColor = true;
			this->startTrackButton->Click += gcnew System::EventHandler(this, &BehaviorRigMainForm::startTrackButton_Click);
			// 
			// stopTrackButton
			// 
			this->stopTrackButton->Location = System::Drawing::Point(13, 128);
			this->stopTrackButton->Name = L"stopTrackButton";
			this->stopTrackButton->Size = System::Drawing::Size(75, 23);
			this->stopTrackButton->TabIndex = 1;
			this->stopTrackButton->Text = L"Stop Track";
			this->stopTrackButton->UseVisualStyleBackColor = true;
			this->stopTrackButton->Click += gcnew System::EventHandler(this, &BehaviorRigMainForm::stopTrackButton_Click);
			// 
			// setUpExperimentButton
			// 
			this->setUpExperimentButton->Location = System::Drawing::Point(13, 35);
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
			this->trackerStatusLabel->Location = System::Drawing::Point(106, 107);
			this->trackerStatusLabel->Name = L"trackerStatusLabel";
			this->trackerStatusLabel->Size = System::Drawing::Size(35, 13);
			this->trackerStatusLabel->TabIndex = 3;
			this->trackerStatusLabel->Text = L"label1";
			// 
			// BehaviorRigMainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(332, 314);
			this->Controls->Add(this->trackerStatusLabel);
			this->Controls->Add(this->setUpExperimentButton);
			this->Controls->Add(this->stopTrackButton);
			this->Controls->Add(this->startTrackButton);
			this->Name = L"BehaviorRigMainForm";
			this->Text = L"BehaviorRig";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void startTrackButton_Click(System::Object^  sender, System::EventArgs^  e) {
				//Disable the start track button
				 this->startTrackButton->Enabled = false;

				 //Enable the stop track button
				 this->stopTrackButton->Enabled = true;

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
			 //experiment->exp.wormAnalysis.DrawResult(experiment->exp.dataOutputLocation + "image" + ".tiff");
			 //zaber->getStagePosition();
			 experiment->WriteCurrentFrameData(testArr, zaber->posX, zaber->posY);
			
			/* experiment->exp.imageControl.grabber.getOverlay()->fill(experiment->exp.imageControl.grabber.getOverlay()->getDropOutColor());
			 RECT rectangle;
			 rectangle.left = (int)testArr[3]-10;
			 rectangle.right = (int)testArr[3]+10;
			 rectangle.top = (int)testArr[4]-10;
			 rectangle.bottom = (int)testArr[4]+10; 
			 experiment->exp.imageControl.grabber.getOverlay()->drawFrameEllipse( RGB(255,0,0), rectangle);
		*/
			 //Move Stage:
			 //zaber->moveStageRelative(testArr[9],  testArr[10]);

			

			 experiment->exp.imageControl.grabber.getOverlay()->fill(experiment->exp.imageControl.grabber.getOverlay()->getDropOutColor());
			 RECT rectangle;
			 rectangle.left = (int)experiment->exp.wormAnalysis.PreviousWormData.Target.x-5;
			 rectangle.right = (int)experiment->exp.wormAnalysis.PreviousWormData.Target.x+5;
			 rectangle.top = (int)experiment->exp.wormAnalysis.PreviousWormData.Target.y-5;
			 rectangle.bottom = (int)experiment->exp.wormAnalysis.PreviousWormData.Target.y+5; 
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
	
	for (int i=1; i<n+1; i++)
	{
	
		if (worker->CancellationPending )
		{
			e->Cancel = true;
		}
		else
		{
		
			experiment->exp.imageControl.GetImage();
			experiment->exp.wormAnalysis.WormImages.OriginalImage = experiment->exp.imageControl.img;
			experiment->exp.wormAnalysis.FindWorm();
		
			experiment->exp.wormAnalysis.WormData.Target.x = experiment->exp.wormAnalysis.WormData.Head.x ;
			experiment->exp.wormAnalysis.WormData.Target.y = experiment->exp.wormAnalysis.WormData.Head.y;
			
			LocalMoveStage = experiment->DetermineStageMovement(experiment->exp.wormAnalysis.WormData.Target.x, experiment->exp.wormAnalysis.WormData.Target.y);
			zaber->getStagePosition();
			zaber->moveStageRelative(LocalMoveStage.x,  LocalMoveStage.y);
			
			experiment->exp.wormAnalysis.DrawResult();
			experiment->exp.videoWriter << experiment->exp.wormAnalysis.WormData.ImageToPrint;

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

			worker->ReportProgress( 0 , dataArray->Clone());
			//Thread::Sleep(1000);
		}
		
		
	}
	return 0;
	}
};
}

