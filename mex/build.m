clear mex;

switch computer
    case 'MACI64'
        mex CXXFLAGS="\$CXXFLAGS -Wall" "-I/opt/local/include" "-L/opt/local/lib" -l "SDL" joystick.cpp
    case {'GLNX86', 'GLNXA64'}
        mex CXXFLAGS="\$CXXFLAGS -Wall" "-I/usr/local/include" "-L/usr/local/lib" -l "SDL" joystick.cpp        
    otherwise
        error('Windows huh? Looks like you''re out of luck today friend')
end