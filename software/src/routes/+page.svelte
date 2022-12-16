<script>
    import { Command } from '@tauri-apps/api/shell'
    import { onMount } from 'svelte';
    import { validate_component } from 'svelte/internal';
    import { writeTextFile, readTextFile, BaseDirectory } from '@tauri-apps/api/fs'
    //import { appWindow } from '@tauri-apps/api/window'
    //import { Config } from  './config.svelte';

    var pageType = 0;

    var modal = 0;

    var load = false;
    var devicelist = [];
    var macro = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'];
    var macroCodes = ['', '', '', '', '', '', '', '', '', '', '', '', '', '', '', '', ];
    var selectedKey = "";
    var keyIsSelected = false;
    var selectedKeyIndex = 0;

    var settings = [false, false, false];

    var selectedDevice = "";

    const translate = (input) => {
        switch (input) {
            case "SPACE":
                
                break;

            case "LCTRL":
                return "Keyboard.write(128);\n"
                break

            case "RCTRL":
                
                break;
        
            case "LALT":
                return "Keyboard.write(130);\n"
                break;
        
            case "RALT":
                
                break;
        
            case "LSHIFT":
                return "Keyboard.write(129);\n"
                break;
        
            case "RSHIFT":
                
                break;
        
            case "BACKSPACE":
                
                break;
        
            case "LWIN":
                
                break;
        
            case "RWIN":
                
                break;
        
            

            default:
                break;
        }
    }

    const exec = async () => {
        document.getElementById("refreshButton").setAttribute("disabled", "");
        load = true;

        devicelist = [];
        const regexp = /\n/g;

        const output = await new Command('list').execute();
        
        let tmp = output.stdout;
        console.log(tmp);

        if (output.stdout != "No boards found.") {
            for (let index = 0; index < output.stdout.match(regexp).length; index++) {
                let startSS = tmp.search(regexp) + 1;
                devicelist.push(tmp.substring(0, startSS));
                tmp = tmp.substring(startSS);
            }

            devicelist.shift();
        } else {
            devicelist.push(output.stdout);
        }
        devicelist = devicelist;

        console.log(devicelist);

        load = false;
        document.getElementById("refreshButton").removeAttribute("disabled");
        /*console.log(tmp.match(regexp))
        console.log()
        console.log(tmp.substring(tmp.search(regexp)));
        let tmp2 = tmp.substring(tmp.search(regexp) + 1);
        console.log(tmp2.substring(tmp.search(regexp)))*/
    }

    const exec2 = () => {
        console.log(devicelist);

        pageType = 1;
    }

    const upload = async () => {
        //document.getElementById("pushToDeviceButton").setAttribute("disabled", "");
        //load = true;

        /*devicelist = [];
        const regexp = /\n/g;

        const output = await new Command('compile').execute();
        
        let tmp = output.stdout;
        console.log(tmp);

        if (output.stdout != "No boards found.") {
            for (let index = 0; index < output.stdout.match(regexp).length; index++) {
                let startSS = tmp.search(regexp) + 1;
                devicelist.push(tmp.substring(0, startSS));
                tmp = tmp.substring(startSS);
            }

            devicelist.shift();
        } else {
            devicelist.push(output.stdout);
        }
        devicelist = devicelist;

        console.log(devicelist);*/

        //load = false;



        document.getElementById("pushToDeviceButton").removeAttribute("disabled");
        
        const init1 = await readTextFile('init1.ino', { dir: BaseDirectory.Resource })
        const init2 = await readTextFile('init2.ino', { dir: BaseDirectory.Resource })

        console.log(init1 + init2);

        var namesTable = "String namesTable[4][4] = {"

        //Adding names
        for (let index = 0; index < 4; index++) {
            namesTable += "{"
            for (let index2 = 0; index2 < 4; index2++) {
                namesTable += "\"" + macro[((index*4)+index2)] + "\","
            }
            namesTable += "},"; 
        }

        //Adding macros
        namesTable += "};\nvoid MacroMap(char in){\nswitch (in) {\n"

        let regexp = /[^}]*/i;
        let regexp2 = /[^\]]*]/i;
        let regexp3 = /:.*:/i;
        let regexp4 = /'.*'/i;

        for (let index = 0; index < 16; index++) {
            namesTable += "case \'" + macro[index] + "\':\n"

            if (macroCodes[index] == 'LU') {
                namesTable += "\nif (layer == maxLayer) {\nlayer=0;\n}else{\nlayer++;\n}\nu8g2.clearBuffer();\nmacroSel(layer);"
            } else if (macroCodes[index] == 'LD') {
                namesTable += "\nif (layer == 0) {\nlayer=maxLayer;\n}else{\nlayer--;\n}\nu8g2.clearBuffer();\nmacroSel(layer);"
            } else {
                //sift through and take out subsections
                console.log(index);
                if (macroCodes[index].match(regexp)) {
                    console.log(macroCodes[index].substring(1).match(regexp))
                    if (macroCodes[index].substring(1).match(regexp2)) {
                        console.log(macroCodes[index].substring(2).match(regexp2));
                        switch (macroCodes[index].substring(2, 3)) {
                            case ":":
                                let tmp = macroCodes[index].substring(2).match(regexp3);
                                console.log("fjkdsl" + translate(tmp));
                                //namesTable += translate(tmp) + "";
                                break;

                            case "'":

                                break;
                        
                            default:
                                break;
                        }
                    }
                }
            }

            namesTable += "\nbreak;\n"
        }

        namesTable += "\ndefault:\nbreak;\n}\nactive=\"\";\n}"
        console.log(init1 + namesTable + init2);
        await writeTextFile('TEST.conf', init1 + namesTable + init2, { dir: BaseDirectory.AppData });
        /*console.log(tmp.match(regexp))
        console.log()
        console.log(tmp.substring(tmp.search(regexp)));
        let tmp2 = tmp.substring(tmp.search(regexp) + 1);
        console.log(tmp2.substring(tmp.search(regexp)))*/
    }

    onMount(async () => {
        await exec();
        document
            .getElementById('titlebar-minimize')
            .addEventListener('click', () => appWindow.minimize())
        document
            .getElementById('titlebar-maximize')
            .addEventListener('click', () => appWindow.toggleMaximize())
        document
            .getElementById('titlebar-close')
            .addEventListener('click', () => appWindow.close())
    })

    const connectAndCreateFile = (input) => {

    }
</script>

{#if modal == 1}
<div class="w-full top-[76px] h-[calc(100vh-150px)] fixed flex z-50 overflow-y-scroll animate-fadein">
    <div class="w-[calc(100%-150px)] p-10 bg-neutral-200 flex flex-col shadow-xl rounded-md  mx-auto my-auto animate-fadein">
        <h1 class="text-6xl font-bold mb-10 mt-10">Settings</h1>
        <h1 class="text-2xl font-bold mx-auto">About</h1>
        <h1 class="mx-auto mt-2">Dyl's MacroPad Software</h1>
        <h1 class="mx-auto mt-2">Software version:</h1>
        <h1 class="mx-auto font-mono">v0.0.1</h1>
        <h1 class="mx-auto mt-2">Documentation:</h1>
        <a  href="https://github.com/dylanmas/" target="_blank" rel="noreferrer noopener" class="font-mono mx-auto">https:/github.com/dylanmas/</a>
        <h1 class="mx-auto mt-2">License:</h1>
        <h1 class="mx-auto font-mono">MIT</h1>
        <h1 class="text-2xl font-bold mx-auto mt-5">Preferences</h1>
        <div class="flex mt-2 py-2 px-4 bg-white rounded-t-md shadow-inner items-center">
            <h1 class="mr-auto">Enable on startup</h1>
            <button on:click={() => {settings[0] = !settings[0]}} class="rounded-full {settings[0] == false ? "bg-red-500" : "bg-blue-500"} w-12 h-6 p-1 shadow-inner">
                <div class="w-4 h-4 transition-all {settings[0] == false ? "" : "ml-auto"} bg-white rounded-full shadow-md"></div>
            </button>
        </div>
        <div class="flex py-2 px-4 bg-white shadow-inner items-center">
            <h1 class="mr-auto">Auto connect</h1>
            <button on:click={() => {settings[1] = !settings[1]}} class="rounded-full {settings[1] == false ? "bg-red-500" : "bg-blue-500"} w-12 h-6 p-1 shadow-inner">
                <div class="w-4 h-4 transition-all {settings[1] == false ? "" : "ml-auto"} bg-white rounded-full shadow-md"></div>
            </button>
        </div>
        <div class="flex py-2 px-4 bg-white rounded-b-md shadow-inner items-center">
            <h1 class="mr-auto">Reset firmware</h1>
            <button on:click={() => {settings[2] = !settings[2]}} class="rounded-full {settings[2] == false ? "bg-red-500" : "bg-blue-500"} w-12 h-6 p-1 shadow-inner">
                <div class="w-4 h-4 transition-all {settings[2] == false ? "" : "ml-auto"} bg-white rounded-full shadow-md"></div>
            </button>
        </div>

        <button on:click={() => {
            modal = 0;
        }} class="flex items-center gap-2 mt-10 bg-blue-300 text-blue-800 px-2 py-1 ml-auto rounded-md text-lg shadow-md hover:bg-blue-200 active:shadow-sm" on:click={exec}>
            Done
        </button>
    </div>
</div>
{:else if modal == 2}
<div class="w-full top-[76px] h-[calc(100vh-150px)] fixed flex z-50 overflow-y-scroll animate-fadein">
    <div class="w-[calc(100%-150px)] p-10 bg-neutral-200 flex flex-col shadow-xl rounded-md  mx-auto my-auto animate-fadein">
        <h1 class="text-6xl font-bold mb-10 mt-10">Are you sure?</h1>
        <h1 class="text-2xl font-bold mx-auto">Any progress on this macro setup will be lost.</h1>
        <div class="flex gap-2">
            <button on:click={() => {
            modal = 0;
            }} class="flex items-center gap-2 mt-10 bg-red-300 text-red-800 px-2 py-1 ml-auto rounded-md text-lg shadow-md hover:bg-red-200 active:shadow-sm" on:click={exec}>
                Cancel
            </button>
            <button on:click={() => {
                modal = 0;
                pageType = 0;
            }} class="flex items-center gap-2 mt-10 bg-blue-300 text-blue-800 px-2 py-1 rounded-md text-lg shadow-md hover:bg-blue-200 active:shadow-sm" on:click={exec}>
                Disconnect
            </button>
        </div>
        
    </div>
</div>
{/if}

<div class="flex flex-col h-[100vh] overflow-x-hidden {modal != 0 ? "opacity-20" : ""}">
    <div data-tauri-drag-region class="titlebar gap-2 text-white w-full h-14 px-10 bg-neutral-600 shadow-md flex fixed items-center">
        <h1 class="mr-auto">Dyl's MacroPad</h1>
        <div class="titlebar-button" id="titlebar-minimize">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
                <path stroke-linecap="round" stroke-linejoin="round" d="M19.5 8.25l-7.5 7.5-7.5-7.5" />
            </svg>
        </div>
        <div class="titlebar-button" id="titlebar-maximize">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
                <path stroke-linecap="round" stroke-linejoin="round" d="M4.5 15.75l7.5-7.5 7.5 7.5" />
            </svg>
        </div>
        <div class="titlebar-button" id="titlebar-close">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
                <path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" />
            </svg>
        </div>
    </div>
    
    <h1 class="animate-fadein font-bold mt-28 mb-4 ml-10 text-5xl pt-[40px]">Macro configurator</h1>
    <div class="animate-fadein w-full py-5 flex items-center">
        <div class="w-full flex flex-col text-3xl">
            <div class="flex items-center px-10">
                <h1 class="text-2xl mr-auto">{pageType == 0 ? "Select your device:" : "Device editor"}</h1>
                <button id="refreshButton" class="{load == true ? "opacity-40" : ""} {pageType != 0 ? "hidden" : ""} flex items-center gap-2 bg-neutral-200 px-2 py-1 ml-5 rounded-md text-xl shadow-md hover:bg-neutral-300 active:shadow-sm" on:click={exec}>
                    <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20" fill="currentColor" class="w-5 h-5">
                        <path fill-rule="evenodd" d="M15.312 11.424a5.5 5.5 0 01-9.201 2.466l-.312-.311h2.433a.75.75 0 000-1.5H3.989a.75.75 0 00-.75.75v4.242a.75.75 0 001.5 0v-2.43l.31.31a7 7 0 0011.712-3.138.75.75 0 00-1.449-.39zm1.23-3.723a.75.75 0 00.219-.53V2.929a.75.75 0 00-1.5 0V5.36l-.31-.31A7 7 0 003.239 8.188a.75.75 0 101.448.389A5.5 5.5 0 0113.89 6.11l.311.31h-2.432a.75.75 0 000 1.5h4.243a.75.75 0 00.53-.219z" clip-rule="evenodd" />
                    </svg>
                    Refresh
                </button>
                <button class="hidden bg-neutral-200 px-2 py-1 ml-5 rounded-md text-xl shadow-md hover:bg-neutral-300 active:shadow-sm" on:click={exec2}>Debug</button>
            </div>
        </div>
    </div>
    
    {#if pageType == 0}
    
    <div class="animate-fadein flex pb-5 mb-auto overflow-x-scroll h-full shadow-md">
        {#if !load}
            {#if devicelist[0] == "No boards found."}
            <div class="bg-neutral-200 w-full mx-10 rounded-md shadow-inner flex flex-col animate-fadein">
                <h1 class="opacity-40 font-bold text-6xl mx-auto mt-auto mb-5">?</h1>
                <h1 class="opacity-40 font-bold text-2xl mx-auto mb-auto">We couldn't find any devices.</h1>
            </div>
            {:else}
            <div class="flex gap-5 pl-10 pb-5">
                {#each devicelist as devicelist, i}
                    <button on:click={() => {connectAndCreateFile(devicelist)}} class="overflow-y-scroll overflow-x-hidden bg-neutral-200 w-80 h-[640px] p-5 rounded-md shadow-md flex flex-col items-center gap-5 hover:bg-neutral-300 active:shadow-sm">
                        <h1 class="text-lg font-bold bg-blue-300 text-blue-800 px-2 py-1 rounded-md shadow-inner font-mono">Device {i + 1}</h1>
                        <img src="https://pdf.icgoo.net/productinfo/allimg/freescale/MC908AP32CFAE.jpg"/>
                        <h1 class="font-semibold text-3xl">{devicelist}</h1>
                    </button>
                {/each}
            </div>
            {/if}
        {:else}
        <div class="bg-neutral-200 w-full mx-10 rounded-md shadow-inner flex flex-col animate-fadein">
            <svg class="animate-spin my-auto mx-auto opacity-30" width="50px" height="50px" viewBox="0 0 20 20" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
                <!-- Uploaded to SVGRepo https://www.svgrepo.com -->
                <title>ic_fluent_spinner_ios_20_filled</title>
                <desc>Created with Sketch.</desc>
                <g id="🔍-System-Icons" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
                    <g id="ic_fluent_spinner_ios_20_filled" fill="#212121" fill-rule="nonzero">
                        <path d="M10,3.5 C6.41015,3.5 3.5,6.41015 3.5,10 C3.5,10.4142 3.16421,10.75 2.75,10.75 C2.33579,10.75 2,10.4142 2,10 C2,5.58172 5.58172,2 10,2 C14.4183,2 18,5.58172 18,10 C18,14.4183 14.4183,18 10,18 C9.58579,18 9.25,17.6642 9.25,17.25 C9.25,16.8358 9.58579,16.5 10,16.5 C13.5899,16.5 16.5,13.5899 16.5,10 C16.5,6.41015 13.5899,3.5 10,3.5 Z" id="🎨-Color"></path>
                    </g>
                </g>
            </svg>
        </div>
        {/if}
    </div>

    {:else if pageType == 1}

    <!-- Editing page -->
    <div class="animate-fadein flex pb-5 mb-auto">
        <div class="bg-neutral-200 w-full mx-10 rounded-md shadow-inner flex flex-col p-5 overflow-x-scroll">
            <h1 class="text-2xl mx-auto mb-4">Select a key to edit</h1>
            <div class="grid grid-cols-4 grid-rows-4 gap-2">
                {#each macro as macro, i}
                <button on:click={() => {selectedKey = macro; selectedKeyIndex = i; keyIsSelected = true;}} class="h-20 bg-neutral-700 rounded-md shadow-md flex items-center hover:bg-black">
                    <h1 class="font-mono font-bold text-white text-3xl mx-auto">{macro}</h1>
                </button>
                {/each}
            </div>
            {#if keyIsSelected == true}
            <div class="flex flex-col mt-2 gap-2 transition-all">
                <div class="bg-white flex items-center shadow-inner rounded-md mt-2">
                    <h1 class="text-2xl m-2 ml-3">Editing:</h1>
                    <div class="w-full h-full flex items-center bg-blue-300 text-blue-700 rounded-md border-blue-700 border-2">
                        <h1 class="font-mono mx-auto font-bold flex text-2xl items-center shadow-sm">{macro[selectedKeyIndex]}</h1>
                    </div>
                </div>
                <div class="bg-white flex flex-col items-center shadow-inner rounded-md mt-2 w-full px-2">
                    <div class="flex mt-2 items-center">
                        <h1 class="text-2xl m-2">Key name:</h1>
                        <div class="bg-neutral-200 flex flex-col items-center shadow-md rounded-md">
                            <textarea bind:value={macro[selectedKeyIndex]} class="font-mono text-xl m-2 bg-transparent resize-none"></textarea>
                        </div>
                    </div>
                    <div class="flex mt-2 items-center mb-2">
                        <h1 class="text-2xl m-2 ml-auto">Key macro:</h1>
                        <div class="bg-neutral-200 flex flex-col items-center shadow-md rounded-md">
                            <textarea bind:value={macroCodes[selectedKeyIndex]} class="font-mono text-xl m-2 bg-transparent resize-none"></textarea>
                        </div>
                    </div>
                </div>
            </div>
            {/if}
            <div id="pushToDeviceButton" class="flex mt-5 text-blue-800 gap-2">
                <button on:click={upload} class="flex items-center gap-2 bg-blue-300 px-2 py-1 ml-auto rounded-md text-lg shadow-md hover:bg-blue-200 active:shadow-sm" on:click={exec}>
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="w-6 h-6">
                <path stroke-linecap="round" stroke-linejoin="round" d="M9 8.25H7.5a2.25 2.25 0 00-2.25 2.25v9a2.25 2.25 0 002.25 2.25h9a2.25 2.25 0 002.25-2.25v-9a2.25 2.25 0 00-2.25-2.25H15m0-3l-3-3m0 0l-3 3m3-3V15" />
                </svg>
                Push to device
                </button>
                <button on:click={() => {modal = 2}} class="flex items-center gap-2 bg-red-300 text-red-800 px-2 py-1 mr-auto rounded-md text-lg shadow-md hover:bg-red-200 active:shadow-sm" on:click={exec}>
                Disconnect
                </button>
            </div>
        </div>
    </div>

    {:else if pageType == 2}

    {/if}

    <!-- Modal screens -->

    <div class="animate-fadein px-10 py-5 bg-neutral-600 text-white">
        <div class="flex items-center">
            <div class="flex flex-col mr-auto">
                <h1 class="text-2xl font-bold">Hello, world!</h1>
                <a href="https://github.com/dylanmas/" target="_blank" rel="noreferrer noopener" class="font-mono">https:/github.com/dylanmas/</a>
            </div>
            <button on:click={() => {
                modal = 1;
            }} class="flex items-center gap-2 bg-neutral-800 px-2 py-1 ml-5 rounded-md text-lg shadow-md hover:bg-black active:shadow-sm" on:click={exec}>
                <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 20 20" fill="currentColor" class="w-5 h-5">
                    <path fill-rule="evenodd" d="M7.84 1.804A1 1 0 018.82 1h2.36a1 1 0 01.98.804l.331 1.652a6.993 6.993 0 011.929 1.115l1.598-.54a1 1 0 011.186.447l1.18 2.044a1 1 0 01-.205 1.251l-1.267 1.113a7.047 7.047 0 010 2.228l1.267 1.113a1 1 0 01.206 1.25l-1.18 2.045a1 1 0 01-1.187.447l-1.598-.54a6.993 6.993 0 01-1.929 1.115l-.33 1.652a1 1 0 01-.98.804H8.82a1 1 0 01-.98-.804l-.331-1.652a6.993 6.993 0 01-1.929-1.115l-1.598.54a1 1 0 01-1.186-.447l-1.18-2.044a1 1 0 01.205-1.251l1.267-1.114a7.05 7.05 0 010-2.227L1.821 7.773a1 1 0 01-.206-1.25l1.18-2.045a1 1 0 011.187-.447l1.598.54A6.993 6.993 0 017.51 3.456l.33-1.652zM10 13a3 3 0 100-6 3 3 0 000 6z" clip-rule="evenodd" />
                </svg>
                Settings
            </button>
        </div>
    </div>
</div>