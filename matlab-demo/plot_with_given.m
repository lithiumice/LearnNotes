function varargout = plot_with_given(varargin)
% PLOT_WITH_GIVEN MATLAB code for plot_with_given.fig
%      PLOT_WITH_GIVEN, by itself, creates a new PLOT_WITH_GIVEN or raises the existing
%      singleton*.
%
%      H = PLOT_WITH_GIVEN returns the handle to a new PLOT_WITH_GIVEN or the handle to
%      the existing singleton*.
%
%      PLOT_WITH_GIVEN('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in PLOT_WITH_GIVEN.M with the given input arguments.
%
%      PLOT_WITH_GIVEN('Property','Value',...) creates a new PLOT_WITH_GIVEN or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before plot_with_given_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to plot_with_given_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help plot_with_given

% Last Modified by GUIDE v2.5 01-Apr-2019 20:52:05

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @plot_with_given_OpeningFcn, ...
                   'gui_OutputFcn',  @plot_with_given_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before plot_with_given is made visible.
function plot_with_given_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to plot_with_given (see VARARGIN)

% Choose default command line output for plot_with_given
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes plot_with_given wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = plot_with_given_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
fun=get(handles.edit1,'string');
fplot(fun,[0,10],'parent',handles.axes1);
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
