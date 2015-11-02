import os, win32api, sys, pythoncom, pyHook

#pyHook and pywin32 must be installed

key_file = os.path.join(os.path.dirname(__file__), 'aa_keycombo.txt')
last_event = False
key_buffer = ''

if os.path.isfile(key_file):
	os.remove(key_file)

def keyboard_handler(e):
	global key_file, last_event, key_buffer
	#exit script on F12
	if e.Key == 'F12':
		f = open(key_file, 'a')
		f.write(key_buffer);
		f.close()
		exit()
	#log other keys
	if e.Ascii > 0:
		key_pressed = str(e.Ascii)
		if last_event:
			key_pressed = 'delay_'+str(e.Time-last_event)+','+key_pressed
		key_buffer += key_pressed+','
		last_event = e.Time
	return True
	
while True:
	hook = pyHook.HookManager()
	hook.KeyDown = keyboard_handler
	hook.HookKeyboard()
	pythoncom.PumpMessages()