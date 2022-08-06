/*
 Copyright (C) 2022 Michael Kondrashin — All Rights Reserved
 You may use, distribute and modify this code under the
 terms of the MIT license.
 You should have received a copy of the MIT license with
 this file. If not, please write to: mkondrashin@gmail.com

 Lates version of this file can be found at following URL:
 https://github.com/mpkondrashin/periculosum

 wrapper.go - example how to use checker
*/

package main

import (
	"bufio"
	"fmt"
	"log"
	"os/exec"
	"time"
)

func main() {
	fmt.Println("Start")
	cmd := exec.Command("./checker")
	stdin, err := cmd.StdinPipe()
	if err != nil {
		log.Fatal(err)
	}
	stdout, err := cmd.StdoutPipe()
	if err != nil {
		log.Fatal(err)
	}
	err = cmd.Start()
	if err != nil {
		return
	}
	r := bufio.NewReader(stdout)

	time.Sleep(200 * time.Millisecond)
	for i := 0; i < 3; i++ {
		stdin.Write([]byte("testdata/malicious/archive.7z\n"))
		time.Sleep(200 * time.Millisecond)
		line, n, err := r.ReadLine()
		fmt.Println(n, err, string(line))
	}
	fmt.Println("run")
}
