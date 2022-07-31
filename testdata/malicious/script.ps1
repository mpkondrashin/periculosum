Param(
    [Parameter(Mandatory = ${true}, ValueFromPipeline = ${true})][Cisco.Ucs.ManagedObject[]] ${Mos},
    [parameter(Mandatory=${true})][string]${FilePath}
)

process
{  
    Try
    {
        ${Error}.Clear()

        if(!(test-path -Path ${FilePath}))
        {
                Write-Host "File Path : ${FilePath} does not exist."
                exit
        }
        
        foreach (${mo} in ${Mos})
        {
            ${fileSource} = ${null}
            
            if (${mo} -is [Cisco.Ucs.SysdebugTechSupport])
            {
                 if (${mo}.OperState -eq "available")
                 {
                     ${fileSource} = "techsupport/" + ${mo}.Name
                 }
            }
            
            if (${mo} -is [Cisco.Ucs.SysdebugCore])
            {               
                ${fileSource} = "corefile/" + ${mo}.Name
            }
            
            if (${fileSource} -ne ${null})
            {
                 ${handle} = ${mo}.Gethandle()
                 ${destFilePath} = ${FilePath} + "\" + ${mo}.Name
                          
                 ${httpAddress} = ${handle}.Uri + "/" + ${fileSource}
                 
                 ${cookie} =  New-Object "System.Net.Cookie"
                 ${cookie}.Name = "ucsm-cookie"
                 ${cookie}.Value = '"' + ${handle}.Cookie + '"'
                 ${cookie}.Domain = ${handle}.Name
                 ${cookieWebClient} =  New-Object "Cisco.Ucs.CookieWebClient"(${cookie})
                 ${cookieWebClient}.Encoding = [System.Text.Encoding]::Unicode
                 
                 ${uri} = New-Object "System.Uri"(${httpAddress})
                 ${cookieWebClient}.DownloadFileAsync(${uri}, ${destFilePath} )
            }            
        }
    }
    Catch
    {
        Write-Host ${Error}
    }
}
