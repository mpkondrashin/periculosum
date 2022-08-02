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
