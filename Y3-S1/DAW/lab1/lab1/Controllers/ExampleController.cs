using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace lab1.Controllers
{
    public class ExampleController : Controller
    {
        // GET: Example
        public ActionResult Index() {
            return View();
        }
        public string Concatenare(string param1, string param2) {
            return param1 + " " + param2;
        }

        public string Produs(int param1, int? param2) {
            if (param2 == null) {
                return "Introduceti ambii parametri";
            }

            int produs = param1 * (int) param2;
            return produs.ToString();
        }

        public string Operatie(int? t1, int? t2, string op) {
            if (t1 == null) {
                return "Introduceti parametrul 1";
            } else if (t2 == null) {
                return "Introduceti parametrul 2";
            } else if (op == null) {
                return "Introduceti parametrul 3";
            }

            int term1 = (int) t1;
            int term2 = (int) t2;
            string operation = (string) op;

            string eq = t1.ToString();
            int res;
            switch (operation) {
            case "plus": {
                eq += " +";
                res = term1 + term2;
                break;
            }
            case "minus": {
                eq += " -";
                res = term1 - term2;
                break;
            }
            case "ori": {
                eq += " *";
                res = term1 * term2;
                break;
            }
            case "div": {
                eq += " /";
                res = term1 / term2;
                break;
            }
            default: {
                res = 0;
                break;
            }
            }

            eq += " " + term2.ToString() + " = " + res.ToString();
            return eq;
        }
    }
}