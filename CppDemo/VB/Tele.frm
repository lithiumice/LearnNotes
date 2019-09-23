VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "上位机"
   ClientHeight    =   3930
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   6585
   LinkTopic       =   "Form1"
   ScaleHeight     =   3930
   ScaleWidth      =   6585
   StartUpPosition =   3  '窗口缺省
   Begin VB.TextBox Text4 
      Height          =   1335
      Left            =   960
      TabIndex        =   6
      Top             =   1680
      Width           =   3375
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   4800
      TabIndex        =   3
      Top             =   1200
      Width           =   735
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   4800
      TabIndex        =   2
      Top             =   480
      Width           =   735
   End
   Begin VB.Timer Timer1 
      Left            =   1800
      Top             =   3240
   End
   Begin VB.CommandButton Command1 
      Caption         =   "发送"
      Height          =   735
      Left            =   4680
      TabIndex        =   1
      Top             =   2160
      Width           =   1815
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   720
      Top             =   3120
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      CommPort        =   3
      DTREnable       =   -1  'True
      BaudRate        =   4800
   End
   Begin VB.TextBox Text1 
      Height          =   1095
      Left            =   840
      TabIndex        =   0
      Top             =   240
      Width           =   3735
   End
   Begin VB.Label Label2 
      Caption         =   "COM"
      Height          =   255
      Left            =   5640
      TabIndex        =   5
      Top             =   1320
      Width           =   375
   End
   Begin VB.Label Label1 
      Caption         =   "bps"
      Height          =   375
      Left            =   5640
      TabIndex        =   4
      Top             =   600
      Width           =   495
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    If MSComm1.InBufferCount > 0 Then Text1.Text = MSComm1.Input
    
    If Text2.Text > 0 Then MSComm1.OutBufferCount = Text2.Text
    

End Sub

Private Sub Form_Load()
    
    MSComm1.PortOpen = True
    Timer1.Enabled = True
    
    
    
End Sub

Private Sub Form_Unload(Cancel As Integer)
MSComm1.PortOpen = False
    Timer1.Enabled = False
End Sub

