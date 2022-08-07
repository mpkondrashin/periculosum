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

package goperic

import (
	"io/fs"
	"path/filepath"
	"strings"
	"testing"
)

func TestGoPeric(t *testing.T) {
	p, err := NewPericlosum("../checker")
	if err != nil {
		t.Fatal(err)
	}
	testdata := "../testdata"
	err = filepath.Walk(testdata, func(path string, info fs.FileInfo, err error) error {
		if err != nil {
			t.Fatalf("%s: %v", path, err)
		}
		if info.IsDir() {
			return nil
		}
		name := filepath.Base(path)
		if name == ".DS_Store" {
			return nil
		}
		var expect bool
		switch {
		case strings.Contains(path, "malicious"):
			expect = true
		case strings.Contains(path, "innocent"):
			expect = false
		default:
			return nil
		}
		//t.Logf("Check file: %s", name)
		result, err := p.Check(path)
		if err != nil {
			t.Fatal(err)
		}
		if result != expect {
			t.Errorf("%s: expected %v, but got %v", path, expect, result)
		} else {
			t.Logf("%s: Ok", name)
		}
		return nil
	})
	if err != nil {
		t.Fatalf("%s: %v", testdata, err)
	}

	/*
		time.Sleep(200 * time.Millisecond)
		result, err := p.Check("../testdata/innocent/test.c\n")
		if err != nil {
			t.Fatal(err)
		}
		if result {
			t.Fatal("Expected false, but got true")
		}*/
}
