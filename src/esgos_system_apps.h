#ifndef __ESGOS_SYSTEM_APPS_H__
#define __ESGOS_SYSTEM_APPS_H__

#define esgos_system_embdded_newline "\n"

#ifndef esgos_system_embedded_home
#define esgos_system_embedded_home_0 "var has_bg=false;"
#define esgos_system_embedded_home_1 "function init(){Core.WriteLine(\"Home Inited.\");has_bg=FS.Exists('/ui/bg.png');}"
#define esgos_system_embedded_home_2 "function wakeup(){Core.WriteLine(\"Home Woke.\"); UI.FillRect(0,0,UI.GetScreenW(),UI.GetScreenH(),UI.GetWhite()); UI.DrawCenterStringFont('Hello', UI.GetScreenW()/2 , UI.GetScreenH()/2,UI.GetFont40())}"
#define esgos_system_embedded_home_3 "function loop(){ }"
#define esgos_system_embedded_home esgos_system_embedded_home_0 esgos_system_embdded_newline esgos_system_embedded_home_1 esgos_system_embdded_newline esgos_system_embedded_home_2 esgos_system_embdded_newline esgos_system_embedded_home_3
#endif

#endif
